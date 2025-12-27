module Zephyr.Renderer.Core.Device;

import Zephyr.Renderer.Core.Device;
import Zephyr.Renderer.OpenGL.Shader;
import Zephyr.Renderer.OpenGL.GlSwapchain;
import Zephyr.Renderer.OpenGL.GlCommandList;
import Zephyr.Renderer.OpenGL.GlPipeline;
import Zephyr.Renderer.OpenGL.GlBuffers;
import Zephyr.Renderer.OpenGL.GlVertexArray;

namespace Zephyr::RHI::Device
{
	Ref<ISwapchain> CreateSwapchain(IWindow& window, SwapchainDesc desc)
	{
		return CreateScope<OpenGL::GlSwapchain>(window, desc);
	}

	Ref<IShader> CreateShader(ShaderCreateInfo createInfo)
	{
		return CreateRef<OpenGL::GlShader>(createInfo);
	}

	Ref<IPipeline> CreatePipeline(GraphicsPipelineDesc desc)
	{
		return CreateRef<OpenGL::GlPipeline>(std::move(desc));
	}

	Ref<ICommandList> CreateCommandList()
	{
		return CreateRef<OpenGL::GlCommandList>();
	}

	Ref<IVertexBuffer> CreateVertexBuffer(BufferDesc desc)
	{
		return CreateRef<OpenGL::GlVertexBuffer>(std::move(desc));
	}

	Ref<IVertexArray> CreateVertexArray(VertexArrayCreateInfo createInfo)
	{
		return CreateRef<OpenGL::GlVertexArray>(std::move(createInfo));
	}
}
