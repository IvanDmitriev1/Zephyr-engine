export module Zephyr.Renderer.Core.Device;

export import Zephyr.Core.CoreTypes;
export import Zephyr.Renderer.IWindow;
export import Zephyr.Renderer.Core.IShader;
export import Zephyr.Renderer.Core.IFrameBuffer;
export import Zephyr.Renderer.Core.IRenderPassEncoder;
export import Zephyr.Renderer.Core.IBuffer;

export namespace Zephyr::RHI::Device
{
	Ref<IFrameBuffer> CreateFrameBuffer(FrameBufferDesc desc);
	Ref<IShader> CreateShader(ShaderCreateInfo createInfo);
	Ref<IPipeline> CreatePipeline(GraphicsPipelineDesc desc);
	Scope<IRenderPassEncoder> CreateRenderPassEncoder(const RenderPassDesc& rp);

	Ref<IBuffer> CreateBuffer(BufferDesc desc);
	Ref<IVertexArray> CreateVertexArray(VertexArrayCreateInfo createInfo);
}