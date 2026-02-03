module;

#include <glad/glad.h> 

export module Zephyr.Renderer.OpenGL.Types.GlBufferTypes;

import Zephyr.Renderer.RHI.Types.BufferTypes;
import Zephyr.Core.Assert;
import std.compat;

export namespace Zephyr::RHI::OpenGL
{
    constexpr GLenum ToGlUsage(BufferAccess access) noexcept
    {
        switch (access)
        {
        case BufferAccess::Static:    return GL_STATIC_DRAW;
        case BufferAccess::Dynamic:   return GL_DYNAMIC_DRAW;
        case BufferAccess::Streaming: return GL_STREAM_DRAW;
		default: Unreachable();
        }
    }

    constexpr uint32_t ToGLTarget(BufferUsage usage) noexcept
    {
        switch (usage)
        {
        case BufferUsage::Vertex:  return GL_ARRAY_BUFFER;
        case BufferUsage::Index:   return GL_ELEMENT_ARRAY_BUFFER;
        case BufferUsage::Uniform: return GL_UNIFORM_BUFFER;
        case BufferUsage::Storage: return GL_SHADER_STORAGE_BUFFER;
		default: Unreachable();
        }
    }
}