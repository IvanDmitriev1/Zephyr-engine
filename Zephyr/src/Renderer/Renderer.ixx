export module Zephyr.Renderer.Renderer;

export import Zephyr.Renderer.Resources.RendererTypes;
export import Zephyr.Renderer.Core.IFrameBuffer;

export namespace Zephyr::Renderer
{
	void Init();
	void Shutdown();

	void BeginFrame();
	void Submit(const DrawItem& item);
	void Submit(std::span<const DrawItem> items);
	void RenderToTarget(Ref<RHI::IFrameBuffer> target, const CameraUniformData& cameraData);
}