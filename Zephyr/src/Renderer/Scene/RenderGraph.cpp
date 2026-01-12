module Zephyr.Renderer.RenderGraph;

namespace Zephyr
{
	RenderGraphPassBuilder RenderGraph::AddPass(std::string name, Ref<RHI::IFrameBuffer> target)
	{
		m_Passes.emplace_back(std::move(name), std::move(target));
		return RenderGraphPassBuilder(m_Passes.back());
	}

	void RenderGraph::Execute(SceneRenderer& renderer)
	{
		for (auto& pass : m_Passes)
		{
			pass.Execute(renderer);
			renderer.ExecutePass(pass.GetDesc());
		}
	}

	void RenderGraph::Clear()
	{
		m_Passes.clear();
	}
}