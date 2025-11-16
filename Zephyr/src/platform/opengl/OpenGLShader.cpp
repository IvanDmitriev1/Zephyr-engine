module;

#include <glad/glad.h>

module zephyr.opengl.OpenGLShader;

namespace zephyr
{
	Ref<IShader> zephyr::IShader::Create(const ShaderCreateInfo& info)
	{
		return CreateRef<OpenGLShader>(info);
	}

	OpenGLShader::OpenGLShader(const ShaderCreateInfo& info)
	{
		std::vector<uint32_t> compiledStages;
		compiledStages.reserve(info.Stages.size());

		for (const auto& stageDesc : info.Stages)
		{
			compiledStages.push_back(CompileShader(stageDesc));
		}

		m_RendererID = glCreateProgram();
		for (auto shader : compiledStages)
		{
			glAttachShader(m_RendererID, shader);
		}

		glLinkProgram(m_RendererID);

		for (auto shader : compiledStages)
			glDeleteShader(shader);

		int success{};
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
		if (success)
		{
			return;
		}

		int length = 0;
		glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &length);
		std::string log(length, '\0');
		glGetProgramInfoLog(m_RendererID, length, &length, log.data());

		glDeleteProgram(m_RendererID);
		m_RendererID = 0;

		throw std::runtime_error(std::format("Shader program link failed: {}", log));
	}

	OpenGLShader::~OpenGLShader()
	{
		if (m_RendererID)
			glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetMat4(std::string_view name, const glm::mat4& value)
	{
		int loc = GetUniformLocation(name);
		glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
	}

	void OpenGLShader::SetVec3(std::string_view name, const glm::vec3& value)
	{
		int loc = GetUniformLocation(name);
		glUniform3fv(loc, 1, &value[0]);
	}

	void OpenGLShader::SetFloat(std::string_view name, float value)
	{
		int loc = GetUniformLocation(name);
		glUniform1f(loc, value);
	}

	constexpr uint32_t OpenGLShader::ToGLShaderStage(ShaderStage stage)
	{
		switch (stage)
		{
		case ShaderStage::Vertex:          return GL_VERTEX_SHADER;
		case ShaderStage::Fragment:        return GL_FRAGMENT_SHADER;
		case ShaderStage::Geometry:        return GL_GEOMETRY_SHADER;
		case ShaderStage::TessControl:     return GL_TESS_CONTROL_SHADER;
		case ShaderStage::TessEvaluation:  return GL_TESS_EVALUATION_SHADER;
		case ShaderStage::Compute:         return GL_COMPUTE_SHADER;
		}
		return 0;
	}

	int OpenGLShader::GetUniformLocation(std::string_view name)
	{
		auto it = m_UniformLocationCache.find(name.data());
		if (it != m_UniformLocationCache.end())
			return it->second;

		int location = glGetUniformLocation(m_RendererID, name.data());
		m_UniformLocationCache.emplace(std::string(name), location);
		return location;
	}

	uint32_t OpenGLShader::CompileShader(const ShaderStageDesc& stageDesc)
	{
		auto size = std::filesystem::file_size(stageDesc.FilePath);
		std::string source(size, '\0');
		std::ifstream in(stageDesc.FilePath, std::ios::in | std::ios::binary);
		if (!in)
		{
			throw std::runtime_error(std::format("Failed to open shader file: {}", stageDesc.FilePath));
		}

		in.read(&source[0], size);

		GLenum glStage = ToGLShaderStage(stageDesc.Stage);
		uint32_t shader = glCreateShader(glStage);

		const char* src = source.c_str();
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		int success{};
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (success)
		{
			return shader;
		}

		int length{};
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::string log(length, '\0');
		glGetShaderInfoLog(shader, length, &length, log.data());

		glDeleteShader(shader);
		throw std::runtime_error(std::format("Shader compile failed ({}) : {}", stageDesc.FilePath, log));
	}
}