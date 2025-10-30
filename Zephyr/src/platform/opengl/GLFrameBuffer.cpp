module;

#include <glad/glad.h>

module zephyr.opengl.GLFrameBuffer;

import zephyr.opengl.GlFrameBufferSpecs;
import zephyr.core.coreTypes;

namespace zephyr
{
	GLFrameBuffer::GLFrameBuffer(const FramebufferSpecification& spec)
		: m_Spec(spec)
	{
		Invalidate();
	}

	GLFrameBuffer::~GLFrameBuffer()
	{
		Destroy();
	}

	void GLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		glViewport(0, 0, (GLsizei)m_Spec.Width, (GLsizei)m_Spec.Height);
	}

	void GLFrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_FBO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		glBlitFramebuffer(
			0, 0, (GLint)Width(), (GLint)Height(),
			0, 0, (GLint)Width(), (GLint)Height(),
			GL_COLOR_BUFFER_BIT, GL_NEAREST);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GLFrameBuffer::ClearAttachment(uint32_t attachmentIndex, int value)
	{
		Assert(attachmentIndex < m_ColorAttachments.size(), "attachmentIndex < ColorAttachments in frameBuffer");
		const auto fmt = m_Spec.Attachments.Attachments[attachmentIndex].TextureFormat;

		if (fmt == FramebufferTextureFormat::RED_INTEGER)
		{
			// Clear integer texture with a single int
			glClearTexImage(m_ColorAttachments[attachmentIndex], 0, GL_RED_INTEGER, GL_INT, &value);
		}
		else
		{
			// Pack a single int into RGBA8 just for demo (0..255 on R)
			unsigned char rgba[4] =
			{
				static_cast<unsigned char>(value & 0xFF), 0, 0, 255
			};

			glClearTexImage(m_ColorAttachments[attachmentIndex], 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
		}
	}

	void GLFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width <= 0 || height <= 0)
			return;

		if (m_Spec.Width == width && m_Spec.Height == height)
			return;

		m_Spec.Width = width;
		m_Spec.Height = height;
		Invalidate();
	}

	uint32_t GLFrameBuffer::GetTexture(uint32_t index)
	{
		if (index >= m_ColorAttachments.size())
			return 0u;

		return m_ColorAttachments[index];
	}

	void GLFrameBuffer::Invalidate()
	{
		Destroy();

		// Create FBO
		glCreateFramebuffers(1, &m_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

		// Create color attachments
		const auto& atts = m_Spec.Attachments.Attachments;
		for (auto& a : atts)
		{
			if (GlFrameBufferSpecs::IsDepth(a.TextureFormat))
				continue;

			GLuint tex = 0;
			glCreateTextures(GL_TEXTURE_2D, 1, &tex);
			glTextureStorage2D(tex, 1, GlFrameBufferSpecs::ToGLInternal(a.TextureFormat), (GLsizei)m_Spec.Width, (GLsizei)m_Spec.Height);

			// Integer attachments must be NEAREST
			const bool isInt = (a.TextureFormat == FramebufferTextureFormat::RED_INTEGER);
			glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, isInt ? GL_NEAREST : GL_LINEAR);
			glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, isInt ? GL_NEAREST : GL_LINEAR);
			glTextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTextureParameteri(tex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			const GLenum attachment = GL_COLOR_ATTACHMENT0 + (GLenum)m_ColorAttachments.size();
			glNamedFramebufferTexture(m_FBO, attachment, tex, 0);
			m_ColorAttachments.push_back(tex);
		}


		// Depth attachment
		const bool wantDepth = std::any_of(atts.begin(), atts.end(),
			[](const FramebufferTextureSpecification& t)
		{
			return GlFrameBufferSpecs::IsDepth(t.TextureFormat);
		});

		if (wantDepth)
		{
			glCreateRenderbuffers(1, &m_RBO);
			glNamedRenderbufferStorage(m_RBO, GL_DEPTH24_STENCIL8, (GLsizei)m_Spec.Width, (GLsizei)m_Spec.Height);
			glNamedFramebufferRenderbuffer(m_FBO, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
		}

		// Draw buffers
		if (m_ColorAttachments.empty())
		{
			glNamedFramebufferDrawBuffer(m_FBO, GL_NONE);
		}
		else
		{
			std::vector<GLenum> bufs(m_ColorAttachments.size());
			for (size_t i = 0; i < bufs.size(); ++i) bufs[i] = GL_COLOR_ATTACHMENT0 + (GLenum)i;
			glNamedFramebufferDrawBuffers(m_FBO, (GLsizei)bufs.size(), bufs.data());
		}

		if (glCheckNamedFramebufferStatus(m_FBO, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			throw std::runtime_error("GLFrameBuffer: incomplete framebuffer");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GLFrameBuffer::Destroy()
	{
		if (m_RBO)
		{
			glDeleteRenderbuffers(1, &m_RBO); m_RBO = 0;
		}

		if (!m_ColorAttachments.empty())
		{
			glDeleteTextures((GLsizei)m_ColorAttachments.size(), m_ColorAttachments.data());
			m_ColorAttachments.clear();
		}

		if (m_FBO)
		{
			glDeleteFramebuffers(1, &m_FBO); m_FBO = 0;
		}
	}
}