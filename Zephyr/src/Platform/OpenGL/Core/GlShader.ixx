export module Zephyr.Renderer.OpenGL.Shader;

export import Zephyr.Renderer.Core.IShader;

export namespace Zephyr::RHI::OpenGL
{
	class GlShader : public IShader
	{
	public:
		explicit GlShader(ShaderCreateInfo createInfo);
		~GlShader() override;

		std::string_view GetName() const noexcept override { return m_Name; }

	public:
		uint32_t GetRendererID() const noexcept { return m_ProgramID; }

		void Bind() const;
		void Unbind() const;

	private:
		void CompileAndLink(std::span<const ShaderStageDesc> stages);
		uint32_t CompileStage(ShaderStage stage, std::string_view source);
		void LinkProgram(std::span<const uint32_t> shaderIDs);

	private:
		std::string m_Name{};
		uint32_t m_ProgramID{};
	};
}