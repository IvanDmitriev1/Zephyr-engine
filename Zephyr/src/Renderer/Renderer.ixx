export module Zephyr.Renderer.Renderer;

export import Zephyr.Core.CoreTypes;
export import Zephyr.Renderer.Core.ISwapchain;

export namespace Zephyr::Renderer
{
	struct InitInfo
	{
		Ref<RHI::ISwapchain> Swapchain{};
	};

	void Init(InitInfo&& info);
	void ShutDown();

	Ref<RHI::IFrameBuffer> GetMainFrameBuffer();
}