export module Zephyr.Renderer.Graph.Passes.DepthPrepass;

export import Zephyr.Renderer.Graph.IRenderGraphPass;

export namespace Zephyr
{
	class DepthPrepass final : public IRenderGraphPass
	{
	public:
		std::string_view GetName() const noexcept override { return "DepthPrepass"; }
		void Execute(PassExecutionContext& ctx) override;
	};
}