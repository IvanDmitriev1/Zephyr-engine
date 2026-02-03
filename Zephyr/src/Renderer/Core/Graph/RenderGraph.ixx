export module Zephyr.Renderer.Graph.RenderGraph;

import Zephyr.Renderer.Graph.IRenderGraphPass;
import std;
import Zephyr.Core.CoreTypes;

export namespace Zephyr
{
	class RenderGraph final
	{
	public:
		template<typename TPass, typename ... Args>
			requires(std::is_base_of_v<IRenderGraphPass, TPass>)
		void AddPass(Args&& ... args)
		{
			auto pass = CreateScope<TPass>(std::forward<Args>(args)...);
			m_Passes.emplace_back(std::move(pass));
		}

		void Execute(PassExecutionContext& context)
		{
			for (auto& pass : m_Passes)
			{
				pass->Execute(context);
			}
		}

	private:
		std::vector<Scope<IRenderGraphPass>> m_Passes;
	};
}
