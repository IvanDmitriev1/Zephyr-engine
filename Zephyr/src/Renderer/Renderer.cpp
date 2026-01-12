module Zephyr.Renderer.Renderer;

import Zephyr.Renderer.SceneRenderer;

namespace Zephyr::Renderer
{
	SceneRenderer* g_SceneRenderer = nullptr;
	RenderGraph* g_renderGraph = nullptr;

	void Init()
	{
		g_SceneRenderer = new SceneRenderer();
		g_renderGraph = new RenderGraph();
	}

	void Shutdown()
	{
		if (g_SceneRenderer)
		{
			delete g_SceneRenderer;
			g_SceneRenderer = nullptr;
		}

		if (g_renderGraph)
		{
			delete g_renderGraph;
			g_renderGraph = nullptr;
		}
	}

	RenderGraph& GetRenderGraph()
	{
		return *g_renderGraph;
	}

	void Submit(const DrawItem& item)
	{
		g_SceneRenderer->Submit(item);
	}

	void Submit(std::span<const DrawItem> items)
	{
		g_SceneRenderer->Submit(items);
	}

	void BeginFrame(const CameraUniformData& cameraData)
	{
		g_SceneRenderer->BeginFrame(cameraData);
	}

	void Render()
	{
		g_renderGraph->Execute(*g_SceneRenderer);
	}
}