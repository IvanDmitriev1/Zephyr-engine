export module Zephyr.Renderer.Graph.IRenderGraphPass;

import Zephyr.Renderer.Types.RenderGraphTypes;

export namespace Zephyr
{
	class IRenderGraphPass
	{
	public:
		virtual ~IRenderGraphPass() = default;

		virtual std::string_view GetName() const noexcept = 0;
		virtual void Execute(PassExecutionContext& ctx) = 0;
	};
}
