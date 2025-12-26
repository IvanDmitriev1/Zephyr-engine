module;

#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.Shader;

import Zephyr.Renderer.OpenGL.Resources.GlShaderTypes;

namespace Zephyr::RHI::OpenGL
{
	namespace
	{
		class ShaderVectorCleanup
		{
		public:
			ShaderVectorCleanup(std::vector<GLuint>& ids)
				:m_ids(ids)
			{}

			~ShaderVectorCleanup()
			{
				for (GLuint id : m_ids)
				{
					if (id)
					{
						glDeleteShader(id);
					}
				}
			}

		private:
			std::vector<GLuint>& m_ids;
		};
	}

	GlShader::GlShader(ShaderCreateInfo createInfo)
		:m_Name(createInfo.Name)
	{
		CompileAndLink(createInfo.Stages);
	}

	GlShader::~GlShader()
	{
		if (m_ProgramID)
			glDeleteProgram(m_ProgramID);
	}

	void GlShader::CompileAndLink(std::span<const ShaderStageDesc> stages)
	{
		std::vector<GLuint> shaderIDs;
		shaderIDs.reserve(stages.size());
		ShaderVectorCleanup cleanup(shaderIDs);

		for (const auto& stageDesc : stages)
		{
			std::string_view source
			{
				reinterpret_cast<const char*>(stageDesc.Code.data()),
				stageDesc.Code.size()
			};

			GLuint shaderID = CompileStage(stageDesc.Stage, source);
			shaderIDs.push_back(shaderID);
		}

		LinkProgram({ shaderIDs.data(), shaderIDs.size() });
	}

	uint32_t GlShader::CompileStage(ShaderStage stage, std::string_view source)
	{
		auto glStage = ToGLStage(stage);
		GLuint shaderID = glCreateShader(glStage);

		std::string stageName = std::format("Shader: {}::stage({})", m_Name, static_cast<int>(stage));
		glObjectLabel(GL_SHADER, shaderID, -1, stageName.c_str());

		const char* sourceCStr = source.data();
		GLint length = static_cast<GLint>(source.size());
		glShaderSource(shaderID, 1, &sourceCStr, &length);
		glCompileShader(shaderID);

		// Check compilation errors
		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (success)
		{
			return shaderID;
		}

		const std::string log = GetShaderInfoLog(shaderID);
		glDeleteShader(shaderID);

		throw std::runtime_error(std::format(
			"Shader compilation failed for {} (stage: {}):\n{}",
			m_Name, static_cast<int>(stage), log
		));
	}

	void GlShader::LinkProgram(std::span<const uint32_t> shaderIDs)
	{
		m_ProgramID = glCreateProgram();

		for (GLuint id : shaderIDs)
		{
			glAttachShader(m_ProgramID, id);
		}

		glLinkProgram(m_ProgramID);
		glObjectLabel(GL_PROGRAM, m_ProgramID, -1, m_Name.c_str());

		GLint success = 0;
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
		if (success)
		{
			return;
		}

		const std::string log = GetProgramInfoLog(m_ProgramID);

		glDeleteProgram(m_ProgramID);
		m_ProgramID = 0;

		throw std::runtime_error(std::format(
			"Shader linking failed for {}:\n{}",
			m_Name, log
		));
	}
}