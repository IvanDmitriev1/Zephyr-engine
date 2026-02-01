export module Zephyr.Renderer.RHI.Device;

export import Zephyr.Core.CoreTypes;
export import Zephyr.Renderer.IWindow;
export import Zephyr.Renderer.RHI.IShader;
export import Zephyr.Renderer.RHI.IFrameBuffer;
export import Zephyr.Renderer.RHI.ICommandBuffer;
export import Zephyr.Renderer.RHI.IBuffer;
export import Zephyr.Renderer.RHI.IVertexArray;
export import Zephyr.Renderer.RHI.IPipeline;

export namespace Zephyr::RHI::Device
{
	Ref<IFrameBuffer> CreateFrameBuffer(FrameBufferDesc desc);
	Ref<IShader> CreateShader(ShaderCreateInfo createInfo);
	Scope<ICommandBuffer> CreateCommandBuffer();
	Ref<IPipeline> CreatePipeline(const GraphicsPipelineDesc& desc);

	Ref<IBuffer> CreateBuffer(BufferDesc desc);
	Ref<IVertexArray> CreateVertexArray(VertexArrayCreateInfo createInfo);
}