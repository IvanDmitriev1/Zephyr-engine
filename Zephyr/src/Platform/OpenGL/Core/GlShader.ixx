export module Zephyr.Renderer.OpenGL.Shader;

export import Zephyr.Renderer.Core.IShader;

export namespace Zephyr::RHI::OpenGL
{
	class GlShader : public IShader
	{
	public:
		explicit GlShader(ShaderCreateInfo createInfo);
		~GlShader() override;

	public:
		std::string_view GetName() const noexcept override
		{
			return m_name;
		}

	public:
		void SetInt(std::string_view name, int value) override;
		void SetFloat(std::string_view name, float value) override;
		void SetFloat2(std::string_view name, const glm::vec2& value) override;
		void SetFloat3(std::string_view name, const glm::vec3& value) override;
		void SetFloat4(std::string_view name, const glm::vec4& value) override;
		void SetMat4(std::string_view name, const glm::mat4& value) override;

	private:
		std::string m_name{};
		uint32_t m_programId{};
	};
}