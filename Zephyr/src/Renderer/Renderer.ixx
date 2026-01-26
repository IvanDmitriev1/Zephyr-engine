export module Zephyr.Renderer.Renderer;

export import Zephyr.Renderer.Types.RendererTypes;
export import Zephyr.Renderer.RHI.IFrameBuffer;

export namespace Zephyr::Renderer
{
	void Init();
	void Shutdown();

	void BeginFrame();
	void Submit(const DrawItem& item);
	void Submit(std::span<const DrawItem> items);
	void RenderToTarget(Ref<RHI::IFrameBuffer> target, const CameraUniformData& cameraData);
}