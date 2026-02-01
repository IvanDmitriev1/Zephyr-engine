export module Zephyr.Renderer.Passes.WireframeOverlayPass;

export import Zephyr.Renderer.IRenderGraphPass;

export namespace Zephyr
{
	class WireframeOverlayPass final : public IRenderGraphPass
	{
	public:
		std::string_view GetName() const noexcept override { return "WireframeOverlayPass"; }

		void Execute(PassExecutionContext& ctx) override;
	};
}