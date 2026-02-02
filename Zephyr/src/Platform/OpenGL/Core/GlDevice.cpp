module Zephyr.Renderer.RHI.Device;

import Zephyr.Renderer.RHI.Device;
import Zephyr.Renderer.OpenGL.Shader;
import Zephyr.Renderer.OpenGL.GlFrameBuffer;
import Zephyr.Renderer.OpenGL.GlRenderPassEncoder;
import Zephyr.Renderer.OpenGL.GlPipeline;
import Zephyr.Renderer.OpenGL.GlBuffer;
import Zephyr.Renderer.OpenGL.GlVertexArray;
import Zephyr.Renderer.OpenGL.GlFrameBuffer;
import Zephyr.Renderer.OpenGL.GlCommandBuffer;

namespace Zephyr::RHI::Device
{
	Ref<IFrameBuffer> CreateFrameBuffer(const FrameBufferDesc& desc)
	{
		return CreateRef<OpenGL::GlFrameBuffer>(desc);
	}

	Ref<IShader> CreateShader(ShaderCreateInfo createInfo)
	{
		return CreateRef<OpenGL::GlShader>(createInfo);
	}

	Scope<ICommandBuffer> CreateCommandBuffer()
	{
		return CreateScope<OpenGL::GlCommandBuffer>();
	}

	Ref<IPipeline> CreatePipeline(const GraphicsPipelineDesc& desc)
	{
		return CreateRef<OpenGL::GlPipeline>(desc);
	}

	Ref<IBuffer> CreateBuffer(BufferDesc desc)
	{
		return CreateRef<OpenGL::GlBuffer>(std::move(desc));
	}

	Ref<IVertexArray> CreateVertexArray(VertexArrayCreateInfo createInfo)
	{
		return CreateRef<OpenGL::GlVertexArray>(std::move(createInfo));
	}


}
