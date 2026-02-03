module;

#include <glad/glad.h> 

export module Zephyr.Renderer.OpenGL.Types.GlShaderTypes;

import Zephyr.Renderer.RHI.Types.ShaderTypes;
import Zephyr.Core.Assert;

export namespace Zephyr::RHI::OpenGL
{
    constexpr GLenum ToGLStage(ShaderStage s)
    {
        switch (s)
        {
        case ShaderStage::Vertex:         return GL_VERTEX_SHADER;
        case ShaderStage::Fragment:       return GL_FRAGMENT_SHADER;
        case ShaderStage::Geometry:       return GL_GEOMETRY_SHADER;
        case ShaderStage::TessControl:    return GL_TESS_CONTROL_SHADER;
        case ShaderStage::TessEvaluation: return GL_TESS_EVALUATION_SHADER;
        case ShaderStage::Compute:        return GL_COMPUTE_SHADER;
		default: Unreachable();
        }
    }

    constexpr std::string GetShaderInfoLog(GLuint shaderID) noexcept
    {
        GLint logLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

        std::string log;
        log.resize(std::max(0, logLength));
        if (logLength > 0)
            glGetShaderInfoLog(shaderID, logLength, nullptr, log.data());

        return log;
    }

    constexpr std::string GetProgramInfoLog(GLuint programID) noexcept
    {
        GLint logLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);

        std::string log;
        log.resize(std::max(0, logLength));
        if (logLength > 0)
            glGetProgramInfoLog(programID, logLength, nullptr, log.data());

        return log;
    }
}