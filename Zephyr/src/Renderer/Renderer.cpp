module Zephyr.Renderer.Renderer;

import Zephyr.Renderer.SceneRenderer;

namespace Zephyr::Renderer
{
	SceneRenderer* g_SceneRenderer = nullptr;

	void Init()
	{
		g_SceneRenderer = new SceneRenderer();
	}

	void Shutdown()
	{
		if (g_SceneRenderer)
		{
			delete g_SceneRenderer;
			g_SceneRenderer = nullptr;
		}
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

	void RenderFrame(const Ref<RHI::IFrameBuffer>&target)
	{
		g_SceneRenderer->RenderFrame(target);
	}
}