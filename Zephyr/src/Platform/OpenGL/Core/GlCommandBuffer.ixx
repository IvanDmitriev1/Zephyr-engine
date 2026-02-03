export module Zephyr.Renderer.OpenGL.GlCommandBuffer;

export import Zephyr.Renderer.RHI.Interfaces.ICommandBuffer;

export namespace Zephyr::RHI::OpenGL
{
	class GlCommandBuffer final : public ICommandBuffer
	{
	public:
		GlCommandBuffer() = default;
		~GlCommandBuffer() noexcept override = default;

		Scope<IRenderEncoder> BeginRenderPass(const RenderPassDesc& desc) override;

		void Execute() override;
	};
}