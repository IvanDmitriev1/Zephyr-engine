module;

#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.GlFrameBuffer;

import Zephyr.Renderer.OpenGL.GlTexture;
import Zephyr.Renderer.OpenGL.Types.GlTextureTypes;
import Zephyr.Renderer.OpenGL.Debug;
import Zephyr.Core.Assert;
import Zephyr.Core.EnumBitmask;

import zephyr.logging.LogHelpers;

namespace Zephyr::RHI::OpenGL
{
	GlFrameBuffer::GlFrameBuffer(const FrameBufferDesc& desc)
		: m_Size(desc.Size),
		m_ColorAttachmentDescs(desc.ColorFormats.begin(), desc.ColorFormats.end()),
		m_DepthAttachmentDesc(desc.DepthFormat),
		m_Name(desc.DebugName)
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

		if (m_Size == newSize)
			return;

		m_Size = newSize;
		Invalidate();
	}

	void GlFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		glViewport(0, 0, (GLsizei)m_Size.Width, (GLsizei)m_Size.Height);
	}

	void GlFrameBuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GlFrameBuffer::ClearForRenderPass(const RenderPassDesc& rp) const
	{
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);

		// Color clears
		for (size_t i = 0; i < rp.Colors.size(); ++i)
		{
			if (rp.Colors[i].Load != LoadOp::Clear)
				continue;

			const float clearColor[4] =
			{
				rp.Colors[i].Clear.R,
				rp.Colors[i].Clear.G,
				rp.Colors[i].Clear.B,
				rp.Colors[i].Clear.A
			};

			glClearNamedFramebufferfv(m_FBO, GL_COLOR, static_cast<GLint>(i), clearColor);
		}

		// Depth / stencil clears
		if (!rp.Depth)
			return;

		const bool clearDepth = (rp.Depth->Load == LoadOp::Clear);
		const bool clearStencil = rp.Depth->ClearStencil;

		if (clearDepth && clearStencil)
		{
			glClearNamedFramebufferfi(
				m_FBO,
				GL_DEPTH_STENCIL,
				0,
				rp.Depth->ClearDepth,
				static_cast<GLint>(rp.Depth->ClearStencil)
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
		Bind();
		Debug::SetGlDebugLabel(GL_FRAMEBUFFER, m_FBO, m_Name);

		CreateAttachments();
		AttachTextures();
		CheckStatus();

		Unbind();
	}

	void GlFrameBuffer::CreateAttachments()
	{
		const size_t count = m_ColorAttachmentDescs.size();
		m_ColorAttachments.clear();
		m_ColorAttachments.reserve(count);

		for (const auto& format : m_ColorAttachmentDescs)
		{
			bool rightFormat = !(format == TextureFormat::Invalid || IsDepth(format));
			Assert(rightFormat, "GlFrameBuffer: invalid color attachment");

			m_ColorAttachments.emplace_back(TextureDesc{
				.Size = m_Size,
				.Format = format,
				.Usage = TextureUsage::RenderTarget | TextureUsage::ShaderRead
											});
		}

		if (m_DepthAttachmentDesc.has_value())
		{
			m_DepthAttachment.emplace(TextureDesc{
				.Size = m_Size,
				.Format = *m_DepthAttachmentDesc,
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
			GLenum attachment = ToGlAttachment(*m_DepthAttachmentDesc);
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
		const GLenum status = glCheckNamedFramebufferStatus(m_FBO, GL_FRAMEBUFFER);

		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			const char* error = "Unknown error";
			switch (status)
			{
			case GL_FRAMEBUFFER_UNDEFINED:
				error = "GL_FRAMEBUFFER_UNDEFINED";
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				error = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
				break;
				// ... more cases
			}

			throw std::runtime_error(
				std::string("GLFrameBuffer: incomplete - ") + error);
		}
	}
}