export module Zephyr.Renderer.OpenGL.GlPipeline;

export import Zephyr.Renderer.RHI.IPipeline;

export namespace Zephyr::RHI::OpenGL
{
	class GlPipeline final : public IPipeline
	{
	public:
		explicit GlPipeline(const GraphicsPipelineDesc& desc);
		~GlPipeline() override = default;

		const GraphicsPipelineDesc& GetDesc() const noexcept override { return m_Desc; }
		void Bind();

	private:
		void ApplyRasterizerState();
		void ApplyDepthState();
		void ApplyBlendState();

	private:
		const GraphicsPipelineDesc m_Desc{};
	};
}