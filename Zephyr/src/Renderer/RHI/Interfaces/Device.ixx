export module Zephyr.Renderer.RHI.Interfaces.Device;

import Zephyr.Core.CoreTypes;
import Zephyr.Renderer.RHI.Interfaces.IShader;
import Zephyr.Renderer.RHI.Interfaces.IFrameBuffer;
import Zephyr.Renderer.RHI.Interfaces.ICommandBuffer;
import Zephyr.Renderer.RHI.Interfaces.IBuffer;
import Zephyr.Renderer.RHI.Interfaces.IVertexArray;
import Zephyr.Renderer.RHI.Interfaces.IPipeline;

export namespace Zephyr::RHI::Device
{
	Ref<IFrameBuffer> CreateFrameBuffer(const FrameBufferDesc& desc);
	Ref<IShader> CreateShader(ShaderCreateInfo createInfo);
	Scope<ICommandBuffer> CreateCommandBuffer();
	Ref<IPipeline> CreatePipeline(const GraphicsPipelineDesc& desc);

	Ref<IBuffer> CreateBuffer(BufferDesc desc);
	Ref<IVertexArray> CreateVertexArray(VertexArrayCreateInfo createInfo);
}
