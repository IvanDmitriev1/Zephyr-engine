export module Zephyr.Renderer.DrawItemRenderer;

export import Zephyr.Renderer.Types.RenderGraphTypes;
export import Zephyr.Renderer.Types.DrawItemRendererTypes;
export import Zephyr.Renderer.RHI.IRenderPassEncoder;

export namespace Zephyr
{
	class DrawItemRenderer final
	{
	public:
		static void RenderCategory(
			RHI::IRenderPassEncoder& encoder,
			const PassExecutionContext& ctx,
			const DrawItemExecutionConfig& config);

	private:
		static void ConfigurePipeline(
			RHI::GraphicsPipelineDesc& desc,
			const DrawItemExecutionConfig& config);

		static void RenderItem(
			RHI::IRenderPassEncoder& encoder,
			const DrawItem& item,
			const PassExecutionContext& ctx);
	};
}