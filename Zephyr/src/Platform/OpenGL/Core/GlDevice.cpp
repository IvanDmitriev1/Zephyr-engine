module Zephyr.Renderer.Core.Device;

import Zephyr.Renderer.Core.Device;
import Zephyr.Renderer.OpenGL.Shader;
import Zephyr.Renderer.OpenGL.GlFrameBuffer;
import Zephyr.Renderer.OpenGL.GlCommandList;
import Zephyr.Renderer.OpenGL.GlPipeline;
import Zephyr.Renderer.OpenGL.GlBuffer;
import Zephyr.Renderer.OpenGL.GlVertexArray;
import Zephyr.Renderer.OpenGL.GlFrameBuffer;

namespace Zephyr::RHI::Device
{
	Ref<IFrameBuffer> CreateFrameBuffer(FrameBufferDesc desc)
	{
		return CreateRef<OpenGL::GlFrameBuffer>(std::move(desc));
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

	Ref<IBuffer> CreateBuffer(BufferDesc desc)
	{
		return CreateRef<OpenGL::GlBuffer>(std::move(desc));
	}

	Ref<IVertexArray> CreateVertexArray(VertexArrayCreateInfo createInfo)
	{
		return CreateRef<OpenGL::GlVertexArray>(std::move(createInfo));
	}
}
