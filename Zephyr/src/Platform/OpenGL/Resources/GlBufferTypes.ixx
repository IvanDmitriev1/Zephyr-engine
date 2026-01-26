module;

#include <glad/glad.h> 

export module Zephyr.Renderer.OpenGL.Resources.GlBufferTypes;

import Zephyr.Renderer.RHI.BufferTypes;

export namespace Zephyr::RHI::OpenGL
{
    constexpr GLenum ToGlUsage(BufferAccess access)
    {
        switch (access)
        {
        case BufferAccess::Static:    return GL_STATIC_DRAW;
        case BufferAccess::Dynamic:   return GL_DYNAMIC_DRAW;
        case BufferAccess::Streaming: return GL_STREAM_DRAW;
        default:
            break;
        }

        throw std::runtime_error("ToGlUsage: unsupported BufferAccess");
    }

    constexpr uint32_t ToGLTarget(BufferUsage usage)
    {
        switch (usage)
        {
        case BufferUsage::Vertex:  return GL_ARRAY_BUFFER;
        case BufferUsage::Index:   return GL_ELEMENT_ARRAY_BUFFER;
        case BufferUsage::Uniform: return GL_UNIFORM_BUFFER;
        case BufferUsage::Storage: return GL_SHADER_STORAGE_BUFFER;
        default:
            break;
        }

        throw std::runtime_error("ToGLTarget: unsupported BufferUsage");
    }
}