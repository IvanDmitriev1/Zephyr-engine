module;

#include <glad/glad.h> 

export module Zephyr.Renderer.OpenGL.Types.GlVertexArrayTypes;

import Zephyr.Renderer.RHI.Types.VertexArrayTypes;

export namespace Zephyr::RHI::OpenGL
{
	constexpr GLenum ToGlBaseType(VertexAttributeType type)
	{
		switch (type)
		{
        case VertexAttributeType::Float:
        case VertexAttributeType::Float2:
        case VertexAttributeType::Float3:
        case VertexAttributeType::Float4:
        case VertexAttributeType::Mat3:
        case VertexAttributeType::Mat4:
            return GL_FLOAT;

        case VertexAttributeType::Int:
        case VertexAttributeType::Int2:
        case VertexAttributeType::Int3:
        case VertexAttributeType::Int4:
            return GL_INT;

        case VertexAttributeType::Bool:
            return GL_UNSIGNED_BYTE;

        default:
            break;
		}

        throw std::runtime_error("ToGlBaseType: unsupported VertexAttributeType");
	}
}