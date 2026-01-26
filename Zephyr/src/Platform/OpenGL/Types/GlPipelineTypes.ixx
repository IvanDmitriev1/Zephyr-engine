module;

#include <glad/glad.h> 

export module Zephyr.Renderer.OpenGL.Types.GlPipelineTypes;

import Zephyr.Renderer.RHI.PipelineTypes;

export namespace Zephyr::RHI::OpenGL
{
    constexpr GLenum ToGlTopology(PrimitiveTopology t) noexcept
    {
        switch (t)
        {
        case PrimitiveTopology::Points:        return GL_POINTS;
        case PrimitiveTopology::Lines:         return GL_LINES;
        case PrimitiveTopology::LineStrip:     return GL_LINE_STRIP;
        case PrimitiveTopology::Triangles:     return GL_TRIANGLES;
        case PrimitiveTopology::TriangleStrip: return GL_TRIANGLE_STRIP;
        }

        return GL_TRIANGLES;
    }
    constexpr GLenum ToGlCompare(CompareOp op) noexcept
    {
        switch (op)
        {
        case CompareOp::Never:        return GL_NEVER;
        case CompareOp::Less:         return GL_LESS;
        case CompareOp::Equal:        return GL_EQUAL;
        case CompareOp::LessEqual:    return GL_LEQUAL;
        case CompareOp::Greater:      return GL_GREATER;
        case CompareOp::NotEqual:     return GL_NOTEQUAL;
        case CompareOp::GreaterEqual: return GL_GEQUAL;
        case CompareOp::Always:       return GL_ALWAYS;
        }
        return GL_LEQUAL;
    }

    constexpr GLenum ToGlCull(CullMode m) noexcept
    {
        switch (m)
        {
        case CullMode::Front:        return GL_FRONT;
        case CullMode::Back:         return GL_BACK;
        case CullMode::FrontAndBack: return GL_FRONT_AND_BACK;
        case CullMode::None:         return GL_BACK;
        }
        return GL_BACK;
    }

    constexpr GLenum ToGlFrontFace(FrontFace f) noexcept
    {
        return (f == FrontFace::Clockwise) ? GL_CW : GL_CCW;
    }
}