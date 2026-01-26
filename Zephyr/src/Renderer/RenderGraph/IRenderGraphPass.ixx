export module Zephyr.Renderer.IRenderGraphPass;

export import Zephyr.Renderer.Types.RenderGraphTypes;
export import Zephyr.Renderer.RenderQueue;

export namespace Zephyr
{
	class IRenderGraphPass
	{
	public:
		virtual ~IRenderGraphPass() = default;

		virtual std::string_view GetName() const noexcept = 0;

		virtual void Initialize() = 0;
		virtual void Execute(PassExecutionContext& ctx) = 0;
	};
}