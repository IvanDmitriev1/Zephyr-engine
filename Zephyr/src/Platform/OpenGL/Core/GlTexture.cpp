module;

#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.GlTexture;

import Zephyr.Renderer.OpenGL.Resources.GlTextureTypes;
import Zephyr.Core.CoreTypes;
import Zephyr.Renderer.OpenGL.Debug;

namespace Zephyr::RHI::OpenGL
{
	GlTexture::GlTexture(TextureDesc desc)
		:m_desc(std::move(desc))
	{
		Invalidate();
	}

	GlTexture::~GlTexture()
	{
		Destroy();
	}

	GlTexture::GlTexture(GlTexture&& other) noexcept
		: m_Id(other.m_Id), m_desc(std::move(other.m_desc))
	{
		other.m_Id = 0;
	}

	GlTexture& GlTexture::operator=(GlTexture&& other) noexcept
	{
		if (this == &other)
			return *this;

		Destroy();
		m_Id = other.m_Id;
		m_desc = std::move(other.m_desc);
		other.m_Id = 0;
		return *this;
	}

	void GlTexture::Destroy() noexcept
	{
		if (m_Id)
		{
			glDeleteTextures(1, &m_Id);
			m_Id = 0;
		}
	}

	void GlTexture::Invalidate()
	{
		Destroy();

		glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);
		Assert(m_Id, "GlTexture: glGenTextures failed");

		GLenum internalFmt = ToGLInternal(m_desc.Format);
		GLenum dataFmt = ToGLFormat(m_desc.Format);
		GLenum dataType = ToGLType(m_desc.Format);

		glTextureStorage2D(m_Id, 1, internalFmt, m_desc.Size.Width, m_desc.Size.Height);

		glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		Debug::SetGlDebugLabel(GL_TEXTURE, m_Id, m_desc.DebugName);
	}
}