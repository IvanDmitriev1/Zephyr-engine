export module Zephyr.Renderer.Passes.DepthPrepass;

export import Zephyr.Renderer.IRenderGraphPass;

export namespace Zephyr
{
	class DepthPrepass final : public IRenderGraphPass
	{
	public:
		std::string_view GetName() const noexcept override { return "DepthPrepass"; }
		void Execute(PassExecutionContext& ctx) override;
	};
}