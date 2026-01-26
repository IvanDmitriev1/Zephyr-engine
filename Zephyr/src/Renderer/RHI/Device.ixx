export module Zephyr.Renderer.RHI.Device;

export import Zephyr.Core.CoreTypes;
export import Zephyr.Renderer.IWindow;
export import Zephyr.Renderer.RHI.IShader;
export import Zephyr.Renderer.RHI.IFrameBuffer;
export import Zephyr.Renderer.RHI.IRenderPassEncoder;
export import Zephyr.Renderer.RHI.IBuffer;

export namespace Zephyr::RHI::Device
{
	Ref<IFrameBuffer> CreateFrameBuffer(FrameBufferDesc desc);
	Ref<IShader> CreateShader(ShaderCreateInfo createInfo);
	Ref<IPipeline> CreatePipeline(GraphicsPipelineDesc desc);
	Scope<IRenderPassEncoder> CreateRenderPassEncoder(const RenderPassDesc& rp);

	Ref<IBuffer> CreateBuffer(BufferDesc desc);
	Ref<IVertexArray> CreateVertexArray(VertexArrayCreateInfo createInfo);
}