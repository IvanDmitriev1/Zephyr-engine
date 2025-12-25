module;

#include <glad/glad.h> 

export module Zephyr.Renderer.OpenGL.Resources.GlTextureTypes;

export import Zephyr.Renderer.Resources.TextureTypes;

export namespace Zephyr::RHI::OpenGL
{
	constexpr GLenum ToGLInternal(TextureFormat fmt)
	{
        switch (fmt)
        {
        case TextureFormat::RGBA8:           return GL_RGBA8;
        case TextureFormat::DEPTH24STENCIL8: return GL_DEPTH24_STENCIL8;
        default:
            break;
        }

        throw std::runtime_error("GlTextureTypes: unsupported TextureFormat");
	}

    constexpr GLenum ToGLFormat(TextureFormat fmt)
    {
        switch (fmt)
        {
        case TextureFormat::RGBA8:                 return GL_RGBA;
        case TextureFormat::DEPTH24STENCIL8:       return GL_DEPTH_STENCIL;
        default:
            break;
        }

        throw std::runtime_error("ToGLFormat: unsupported TextureFormat");
    }

    constexpr GLenum ToGLType(TextureFormat fmt)
    {
        switch (fmt)
        {
        case TextureFormat::RGBA8:                 return GL_UNSIGNED_BYTE;
        case TextureFormat::DEPTH24STENCIL8:       return GL_UNSIGNED_INT_24_8;
        default:
            break;
        }

        throw std::runtime_error("ToGLType: unsupported TextureFormat");
    }

    constexpr GLenum ToGlAttachment(TextureFormat fmt)
    {
        switch (fmt)
        {
        case TextureFormat::DEPTH24STENCIL8: return GL_DEPTH_STENCIL_ATTACHMENT;
        default:
            break;
        }

        throw std::runtime_error("ToGlAttachment: unsupported TextureFormat");
    }
}