export module zephyr.opengl.OpenGLShader;

export import zephyr.renderer.IShader;
import std.compat;

export namespace zephyr
{
	class OpenGLShader : public IShader
	{
	public:
		explicit OpenGLShader(const ShaderCreateInfo& info);
		~OpenGLShader() override;
	public:
		void Bind() const override;
		void Unbind() const override;

		void SetMat4(std::string_view name, const glm::mat4& value) override;
		void SetVec3(std::string_view name, const glm::vec3& value) override;
		void SetFloat(std::string_view name, float value) override;

	private:
		constexpr uint32_t ToGLShaderStage(ShaderStage stage);
		int GetUniformLocation(std::string_view name);
		uint32_t CompileShader(const ShaderStageDesc& stageDesc);

	private:
		uint32_t m_RendererID = 0;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};
}