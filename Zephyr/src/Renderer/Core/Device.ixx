export module Zephyr.Renderer.Core.Device;

export import Zephyr.Core.CoreTypes;
export import Zephyr.Renderer.IWindow;
export import Zephyr.Renderer.Core.IShader;
export import Zephyr.Renderer.Core.ISwapchain;
export import Zephyr.Renderer.Core.ICommandList;
export import Zephyr.Renderer.Core.IBuffer;

export namespace Zephyr::RHI::Device
{
	Ref<ISwapchain> CreateSwapchain(IWindow& window, SwapchainDesc desc);
	Ref<IShader> CreateShader(ShaderCreateInfo createInfo);
	Ref<IPipeline> CreatePipeline(GraphicsPipelineDesc desc);
	Ref<ICommandList> CreateCommandList();

	Ref<IVertexBuffer> CreateVertexBuffer(BufferDesc desc);
	Ref<IVertexArray> CreateVertexArray(VertexArrayCreateInfo createInfo);
}