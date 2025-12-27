module;

#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.GlFrameBuffer;

import Zephyr.Renderer.OpenGL.GlTexture;
import Zephyr.Renderer.OpenGL.Resources.GlTextureTypes;
import Zephyr.Renderer.OpenGL.Resources.GlFrameBufferHelpers;
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

	void GlFrameBuffer::Resize(glm::ivec2 newSize)
	{
		if (m_Spec.Size == newSize || (m_Spec.Size.x == 0 && m_Spec.Size.y== 0))
			return;
		
		m_Spec.Size = newSize;
		Invalidate();
	}

	void GlFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);
		glViewport(0, 0, (GLsizei)m_Spec.Size.x, (GLsizei)m_Spec.Size.y);
	}

	void GlFrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_FBO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		int width = m_Spec.Size.x;
		int height = m_Spec.Size.y;

		glBlitFramebuffer(
			0, 0, width, height,
			0, 0, width, height,
			GL_COLOR_BUFFER_BIT, GL_NEAREST);

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	void GlFrameBuffer::ClearForRenderPass(const RenderPassDesc& rp)
	{
		ClearNamedFbo(rp, m_FBO);
	}

	void GlFrameBuffer::ClearDefaultFrameBuffer(const RenderPassDesc& rp)
	{
		ClearDefaultFbo(rp);
	}

	void GlFrameBuffer::Destroy() noexcept
	{
		if (m_FBO)
		{
			glDeleteRenderbuffers(1, &m_FBO);
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

		CreateAttachments();
		AttachTextures();
		CheckStatus();

		Debug::SetGlDebugLabel(GL_FRAMEBUFFER, m_FBO, m_Spec.DebugName);
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