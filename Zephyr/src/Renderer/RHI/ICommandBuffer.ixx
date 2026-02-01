export module Zephyr.Renderer.RHI.ICommandBuffer;

export import Zephyr.Core.CoreTypes;
export import Zephyr.Renderer.RHI.RenderPassTypes;
export import Zephyr.Renderer.RHI.IRenderEncoder;

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