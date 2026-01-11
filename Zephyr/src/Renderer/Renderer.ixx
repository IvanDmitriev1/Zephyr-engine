export module Zephyr.Renderer.Renderer;

export import Zephyr.Core.CoreTypes;
export import Zephyr.Renderer.Core.IRenderPassEncoder;
export import Zephyr.Renderer.Resources.RendererTypes;

export namespace Zephyr::Renderer
{
	void Init();
	void Shutdown();
	
	void Submit(const DrawItem& item);
	void Submit(std::span<const DrawItem> items);

	void BeginFrame(const CameraUniformData& cameraData);
	void RenderFrame(const Ref<RHI::IFrameBuffer>& target);
}