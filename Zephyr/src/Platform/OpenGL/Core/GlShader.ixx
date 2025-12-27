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
			return m_Name;
		}

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