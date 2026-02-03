export module Zephyr.Renderer.RHI.Interfaces.ICommandBuffer;

export import Zephyr.Core.CoreTypes;
export import Zephyr.Renderer.RHI.Types.RenderPassTypes;
export import Zephyr.Renderer.RHI.Interfaces.IRenderEncoder;

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