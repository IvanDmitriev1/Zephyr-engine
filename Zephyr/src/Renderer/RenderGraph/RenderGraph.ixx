export module Zephyr.Renderer.RenderGraph;

export import Zephyr.Renderer.IRenderGraphPass;

export namespace Zephyr
{
	class RenderGraph final
	{
	public:
		void AddPass(Scope<IRenderGraphPass> pass)
		{
			m_Passes.push_back(std::move(pass));
		}

		void Initialize()
		{
			for (auto& pass : m_Passes)
				pass->Initialize();
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