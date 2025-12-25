module Zephyr.Renderer.Core.Device;

import Zephyr.Renderer.Core.Device;
import Zephyr.Renderer.OpenGL.Shader;
import Zephyr.Renderer.OpenGL.GlSwapchain;

namespace Zephyr::RHI::Device
{
	Scope<ISwapchain> CreateSwapchain(IWindow& window, SwapchainDesc desc)
	{
		return CreateScope<OpenGL::GlSwapchain>(window, desc);
	}

	Ref<IShader> CreateShader(ShaderCreateInfo createInfo)
	{
		return CreateRef<OpenGL::GlShader>(createInfo);
	}
}
