export module Zephyr.Renderer.Graph.Passes.WireframeOverlayPass;

import Zephyr.Renderer.Graph.IRenderGraphPass;

export namespace Zephyr
{
	class WireframeOverlayPass final : public IRenderGraphPass
	{
	public:
		std::string_view GetName() const noexcept override { return "WireframeOverlayPass"; }

		void Execute(PassExecutionContext& ctx) override;
	};
}
