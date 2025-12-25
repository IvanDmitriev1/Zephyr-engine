module;

#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.GlTexture;

import Zephyr.Renderer.OpenGL.Resources.GlTextureTypes;
import Zephyr.Core.CoreTypes;

namespace Zephyr::RHI::OpenGL
{
	GlTexture::GlTexture(TextureDesc desc)
		:m_desc(std::move(desc))
	{
		Invalidate();
	}

	GlTexture::~GlTexture()
	{
		if (m_Id)
		{
			glDeleteTextures(1, &m_Id);
		}
	}

	void GlTexture::Invalidate()
	{
		if (m_Id)
			glDeleteTextures(1, &m_Id);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);
		Assert(m_Id, "GlTexture: glGenTextures failed");

		GLenum internalFmt = ToGLInternal(m_desc.Format);
		GLenum dataFmt = ToGLFormat(m_desc.Format);
		GLenum dataType = ToGLType(m_desc.Format);

		glTextureStorage2D(m_Id, 1, internalFmt, m_desc.Size.x, m_desc.Size.y);

		glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		if (!m_desc.DebugName.empty())
		{
			glObjectLabel(GL_TEXTURE, m_Id, -1, m_desc.DebugName.data());
		}
	}
}