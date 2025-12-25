export module Zephyr.Renderer.Core.Device;

export import Zephyr.Core.CoreTypes;
export import Zephyr.Renderer.IWindow;
export import Zephyr.Renderer.Core.IShader;
export import Zephyr.Renderer.Core.ISwapchain;

export namespace Zephyr::RHI::Device
{
	Scope<ISwapchain> CreateSwapchain(IWindow& window, SwapchainDesc desc);
	Ref<IShader> CreateShader(ShaderCreateInfo createInfo);
}