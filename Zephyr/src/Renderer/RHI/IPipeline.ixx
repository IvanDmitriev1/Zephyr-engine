export module Zephyr.Renderer.RHI.IPipeline;

export import Zephyr.Renderer.RHI.PipelineTypes;

export namespace Zephyr::RHI
{
	class IPipeline
	{
	public:
		virtual ~IPipeline() = default;
		virtual const GraphicsPipelineDesc& GetDesc() const noexcept = 0;
	};
}