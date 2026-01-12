export module Zephyr.Renderer.Renderer;

export import Zephyr.Renderer.RenderGraph;

export namespace Zephyr::Renderer
{
	void Init();
	void Shutdown();
	RenderGraph& GetRenderGraph();

	void Submit(const DrawItem& item);
	void Submit(std::span<const DrawItem> items);

	void BeginFrame(const CameraUniformData& cameraData);
	void Render();
}