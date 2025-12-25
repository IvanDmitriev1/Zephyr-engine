module Zephyr.Renderer.OpenGL.Shader;

namespace Zephyr::RHI::OpenGL
{
	GlShader::GlShader(ShaderCreateInfo createInfo)
	{
	}

	GlShader::~GlShader()
	{
	}

	void GlShader::SetInt(std::string_view name, int value)
	{}
	void GlShader::SetFloat(std::string_view name, float value)
	{}
	void GlShader::SetFloat2(std::string_view name, const glm::vec2 & value)
	{}
	void GlShader::SetFloat3(std::string_view name, const glm::vec3 & value)
	{}
	void GlShader::SetFloat4(std::string_view name, const glm::vec4 & value)
	{}
	void GlShader::SetMat4(std::string_view name, const glm::mat4 & value)
	{}
}