export module Zephyr.Renderer.RHI.Interfaces.Device;

export import Zephyr.Core.CoreTypes;
export import Zephyr.Renderer.Platform.IWindow;
export import Zephyr.Renderer.RHI.Interfaces.IShader;
export import Zephyr.Renderer.RHI.Interfaces.IFrameBuffer;
export import Zephyr.Renderer.RHI.Interfaces.ICommandBuffer;
export import Zephyr.Renderer.RHI.Interfaces.IBuffer;
export import Zephyr.Renderer.RHI.Interfaces.IVertexArray;
export import Zephyr.Renderer.RHI.Interfaces.IPipeline;

export namespace Zephyr::RHI::Device
{
	Ref<IFrameBuffer> CreateFrameBuffer(const FrameBufferDesc& desc);
	Ref<IShader> CreateShader(ShaderCreateInfo createInfo);
	Scope<ICommandBuffer> CreateCommandBuffer();
	Ref<IPipeline> CreatePipeline(const GraphicsPipelineDesc& desc);

	Ref<IBuffer> CreateBuffer(BufferDesc desc);
	Ref<IVertexArray> CreateVertexArray(VertexArrayCreateInfo createInfo);
}