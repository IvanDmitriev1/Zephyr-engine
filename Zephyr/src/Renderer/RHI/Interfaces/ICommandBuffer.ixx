export module Zephyr.Renderer.RHI.Interfaces.ICommandBuffer;

import Zephyr.Core.CoreTypes;
import Zephyr.Renderer.RHI.Types.RenderPassTypes;
import Zephyr.Renderer.RHI.Interfaces.IRenderEncoder;

export namespace Zephyr::RHI
{
	class ICommandBuffer
	{
	public: 
		virtual ~ICommandBuffer() noexcept = default;

		virtual Scope<IRenderEncoder> BeginRenderPass(const RenderPassDesc& desc) = 0;

		virtual void Execute() = 0;
	};
}
