export module Zephyr.Renderer.OpenGL.GlPipeline;

export import Zephyr.Renderer.Core.IPipeline;

export namespace Zephyr::RHI::OpenGL
{
	class GlPipeline final : public IPipeline
	{
	public:
		explicit GlPipeline(GraphicsPipelineDesc desc);

		const GraphicsPipelineDesc& GetDesc() const noexcept override
		{
			return m_Desc;
		}

		void ApplyState();

	private:
		void ApplyRasterizerState();
		void ApplyDepthState();
		void ApplyBlendState();

	private:
		const GraphicsPipelineDesc m_Desc{};
	};
}