export module Zephyr.Renderer.RHI.Interfaces.IPipeline;

export import Zephyr.Renderer.RHI.Types.PipelineTypes;

export namespace Zephyr::RHI
{
	class IPipeline
	{
	public:
		virtual ~IPipeline() = default;
		virtual const GraphicsPipelineDesc& GetDesc() const noexcept = 0;
	};
}