module;

#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.GlTexture;

import Zephyr.Renderer.OpenGL.Types.GlTextureTypes;
import Zephyr.Core.CoreTypes;
import Zephyr.Renderer.OpenGL.Debug;

namespace Zephyr::RHI::OpenGL
{
	GlTexture::GlTexture(const TextureDesc& desc)
		: m_Size(desc.Size),
		m_Format(desc.Format),
		m_MipLevels(desc.MipLevels > 0 ? desc.MipLevels : 1),
		m_ArrayLayers(desc.ArrayLayers > 0 ? desc.ArrayLayers : 1),
		m_Name(desc.DebugName)
	{
		Invalidate();
	}

	GlTexture::~GlTexture()
	{
		Destroy();
	}

	GlTexture::GlTexture(GlTexture&& other) noexcept
		: m_Size(other.m_Size)
		, m_Format(other.m_Format)
		, m_MipLevels(other.m_MipLevels)
		, m_ArrayLayers(other.m_ArrayLayers)
		, m_Name(std::move(other.m_Name))
		, m_Id(std::exchange(other.m_Id, 0u))
	{
		other.m_Size = {};
		other.m_Format = TextureFormat::Invalid;
		other.m_MipLevels = 1;
		other.m_ArrayLayers = 1;
	}

	GlTexture& GlTexture::operator=(GlTexture&& other) noexcept
	{
		if (this == &other)
			return *this;

		Destroy();

		m_Size = other.m_Size;
		m_Format = other.m_Format;
		m_MipLevels = other.m_MipLevels;
		m_ArrayLayers = other.m_ArrayLayers;
		m_Name = std::move(other.m_Name);
		m_Id = std::exchange(other.m_Id, 0u);

		other.m_Size = {};
		other.m_Format = TextureFormat::RGBA8;
		other.m_MipLevels = 1;
		other.m_ArrayLayers = 1;

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

		GLint target;

		if (m_ArrayLayers > 1)
			target = GL_TEXTURE_2D_ARRAY;
		else
			target = GL_TEXTURE_2D;

		glCreateTextures(target, 1, &m_Id);
		Assert(m_Id, "GlTexture: glGenTextures failed");

		GLenum internalFmt = ToGLInternal(m_Format);
		GLenum dataFmt = ToGLFormat(m_Format);
		GLenum dataType = ToGLType(m_Format);

		if (target == GL_TEXTURE_2D_ARRAY)
		{
			glTextureStorage3D(
				m_Id,
				m_MipLevels,
				internalFmt,
				m_Size.Width,
				m_Size.Height,
				m_ArrayLayers
			);
		}
		else
		{
			glTextureStorage2D(
				m_Id,
				m_MipLevels,
				internalFmt,
				m_Size.Width,
				m_Size.Height
			);
		}

		glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER,
							m_MipLevels > 1 ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
		glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		Debug::SetGlDebugLabel(GL_TEXTURE, m_Id, m_Name);
	}
}