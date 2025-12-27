export module Zephyr.Renderer.Core.IPipeline;

export import Zephyr.Renderer.Resources.PipelineTypes;

export namespace Zephyr::RHI
{
	class IPipeline
	{
	public:
		virtual ~IPipeline() = default;
		virtual const GraphicsPipelineDesc& GetDesc() const noexcept = 0;
	};
}