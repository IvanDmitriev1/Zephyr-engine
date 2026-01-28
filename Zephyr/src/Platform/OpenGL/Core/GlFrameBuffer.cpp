module;

#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.GlFrameBuffer;

import Zephyr.Renderer.OpenGL.GlTexture;
import Zephyr.Renderer.OpenGL.Types.GlTextureTypes;
import Zephyr.Renderer.OpenGL.Debug;

namespace Zephyr::RHI::OpenGL
{
	GlFrameBuffer::GlFrameBuffer(FrameBufferDesc desc)
		:m_Spec(std::move(desc))
	{
		Invalidate();
	}

	GlFrameBuffer::~GlFrameBuffer()
	{
		Destroy();
	}

	const ITexture& GlFrameBuffer::GetColorAttachment(size_t index) const
	{
		Assert(index < m_ColorAttachments.size(), "GlFrameBuffer: index out of range");
		return m_ColorAttachments[index];
	}

	void GlFrameBuffer::Resize(Extent2D newSize)
	{
		if (newSize.Width == 0 || newSize.Height == 0)
			return;

		if (m_Spec.Size == newSize)
			return;
		
		m_Spec.Size = newSize;
		Invalidate();
	}

	void GlFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		glViewport(0, 0, (GLsizei)m_Spec.Size.Width, (GLsizei)m_Spec.Size.Height);

		glEnable(GL_SCISSOR_TEST);
		glScissor(0, 0, (GLsizei)m_Spec.Size.Width, (GLsizei)m_Spec.Size.Height);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}

	void GlFrameBuffer::ClearForRenderPass(const RenderPassDesc& rp)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

		// Color clears
		for (size_t i = 0; i < rp.Colors.size(); ++i)
		{
			if (rp.Colors[i].Load != LoadOp::Clear)
				continue;

			const std::array<float, 4> arr = {
				rp.Colors[i].Clear.R,
				rp.Colors[i].Clear.G,
				rp.Colors[i].Clear.B,
				rp.Colors[i].Clear.A
			};

			glClearNamedFramebufferfv(m_FBO, GL_COLOR, (GLint)i, arr.data());
		}

		// Depth / stencil clears
		if (!rp.Depth)
			return;

		const bool clearDepth = (rp.Depth->Load == LoadOp::Clear);
		const bool clearStencil = rp.Depth->ClearStencilEnable;

		if (clearDepth && clearStencil)
		{
			glClearNamedFramebufferfi(
				m_FBO,
				GL_DEPTH_STENCIL,
				0,
				rp.Depth->ClearDepth,
				(GLint)rp.Depth->ClearStencil
			);
		}
		else if (clearDepth)
		{
			const auto depth = rp.Depth->ClearDepth;
			glClearNamedFramebufferfv(m_FBO, GL_DEPTH, 0, &depth);
		}
		else if (clearStencil)
		{
			const auto stencil = (GLint)rp.Depth->ClearStencil;
			glClearNamedFramebufferiv(m_FBO, GL_STENCIL, 0, &stencil);
		}
	}

	void GlFrameBuffer::Destroy() noexcept
	{
		if (m_FBO)
		{
			glDeleteFramebuffers(1, &m_FBO);
			m_FBO = 0;
		}

		m_ColorAttachments.clear();
		m_DepthAttachment.reset();
	}

	void GlFrameBuffer::Invalidate()
	{
		Destroy();

		glCreateFramebuffers(1, &m_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		Debug::SetGlDebugLabel(GL_FRAMEBUFFER, m_FBO, m_Spec.DebugName);

		CreateAttachments();
		AttachTextures();
		CheckStatus();
	}

	void GlFrameBuffer::CreateAttachments()
	{
		const auto& atts = m_Spec.ColorAttachments;
		m_ColorAttachments.reserve(atts.size());

		for (auto& a : atts)
		{
			bool rightFormat = !(a.Format == TextureFormat::None || IsDepth(a.Format));
			Assert(rightFormat, "GlFrameBuffer: invalid color attachment");

			m_ColorAttachments.emplace_back(
				TextureDesc
				{
					.Size = m_Spec.Size,
					.Format = a.Format,
					.Usage = TextureUsage::RenderTarget | TextureUsage::ShaderRead
				});
		}


		if (m_Spec.DepthStencilAttachment.has_value())
		{
			m_DepthAttachment.emplace(TextureDesc
									  {
										  .Size = m_Spec.Size,
										  .Format = m_Spec.DepthStencilAttachment->Format,
										  .Usage = TextureUsage::RenderTarget | TextureUsage::ShaderRead
									  });
		}
	}

	void GlFrameBuffer::AttachTextures()
	{
		// Attach color textures
		if (m_ColorAttachments.empty())
		{
			glNamedFramebufferDrawBuffer(m_FBO, GL_NONE);
		}
		else
		{
			std::vector<GLenum> bufs(m_ColorAttachments.size());
			for (size_t i = 0; i < bufs.size(); ++i)
			{
				const GLenum attachment = GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(i);
				glNamedFramebufferTexture(m_FBO, attachment, m_ColorAttachments[i].GetId(), 0);

				bufs[i] = attachment;
			}

			glNamedFramebufferDrawBuffers(m_FBO, (GLsizei)bufs.size(), bufs.data());
		}

		if (m_DepthAttachment)
		{
			GLenum attachment = ToGlAttachment(m_Spec.DepthStencilAttachment->Format);
			glNamedFramebufferTexture(
				m_FBO,
				attachment,
				m_DepthAttachment->GetId(),
				0
			);
		}
	}

	void GlFrameBuffer::CheckStatus()
	{
		if (glCheckNamedFramebufferStatus(m_FBO, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			throw std::runtime_error("GLFrameBuffer: incomplete framebuffer");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}