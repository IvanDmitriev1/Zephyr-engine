module;

#include <glad/glad.h> 

export module Zephyr.Renderer.OpenGL.Types.GlTextureTypes;

import Zephyr.Renderer.RHI.Types.TextureTypes;
import Zephyr.Core.Assert;

export namespace Zephyr::RHI::OpenGL
{
	constexpr GLenum ToGLInternal(TextureFormat fmt) noexcept
	{
        switch (fmt)
        {
        case TextureFormat::RGBA8:           return GL_RGBA8;
		case TextureFormat::RGBA16F:         return GL_RGBA16F;
        case TextureFormat::DEPTH24STENCIL8: return GL_DEPTH24_STENCIL8;
		default: Unreachable();
        }
	}

    constexpr GLenum ToGLFormat(TextureFormat fmt) noexcept
    {
        switch (fmt)
        {
        case TextureFormat::RGBA8:
        case TextureFormat::RGBA16F:               return GL_RGBA;
        case TextureFormat::DEPTH24STENCIL8:       return GL_DEPTH_STENCIL;
		default: Unreachable();
        }
    }

    constexpr GLenum ToGLType(TextureFormat fmt) noexcept
    {
        switch (fmt)
        {
        case TextureFormat::RGBA8:                 return GL_UNSIGNED_BYTE;
        case TextureFormat::RGBA16F:               return GL_FLOAT;
        case TextureFormat::DEPTH24STENCIL8:       return GL_UNSIGNED_INT_24_8;
		default: Unreachable();
        }
    }

    constexpr GLenum ToGlAttachment(TextureFormat fmt) noexcept
    {
        switch (fmt)
        {
        case TextureFormat::DEPTH24STENCIL8: return GL_DEPTH_STENCIL_ATTACHMENT;
		default: Unreachable();
        }
    }
}