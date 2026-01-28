export module Zephyr.Renderer.BaseGeometryPass;

export import Zephyr.Renderer.IRenderGraphPass;
export import Zephyr.Renderer.RHI.IRenderPassEncoder;

export namespace Zephyr
{
	class BaseGeometryPass : public IRenderGraphPass
	{
	protected:
		void RenderPhases(
			RHI::IRenderPassEncoder& encoder,
			const PassExecutionContext& context,
			std::span<const DrawCategory> categoryToRender);

	private:
		void ConfigurePipelineForPhase(RHI::GraphicsPipelineDesc& desc, DrawCategory category);
	};
}