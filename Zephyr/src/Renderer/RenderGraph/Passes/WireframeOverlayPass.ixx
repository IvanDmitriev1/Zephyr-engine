export module Zephyr.Renderer.Passes.WireframeOverlayPass;

export import Zephyr.Renderer.IRenderGraphPass;
import Zephyr.Renderer.RHI.Device;
import Zephyr.Renderer.DrawItemRenderer;


export namespace Zephyr
{
	class WireframeOverlayPass final : public IRenderGraphPass
	{
	public:
		std::string_view GetName() const noexcept override { return "WireframeOverlayPass"; }

		void Execute(PassExecutionContext& ctx) override
		{
			if (ctx.RenderMode != ViewportRenderMode::Wireframe)
				return;

			RHI::RenderPassDesc passDesc{
				.Target = ctx.Target,
				.Colors = std::to_array<RHI::ColorAttachment>({
					{
						.Load = RHI::LoadOp::Clear,
						.Store = RHI::StoreOp::Store
					}
				}),
				.Depth = RHI::DepthAttachment{
					.Load = RHI::LoadOp::Load,
					.Store = RHI::StoreOp::Store,
				},
				.DebugName = "WireframeOverlayPass"
			};

			auto encoder = RHI::Device::CreateRenderPassEncoder(passDesc);

			auto cameraBinding = std::to_array<RHI::ResourceBinding>({
				{ RHI::UniformBindings::Camera, ctx.Resources.CameraBuffer }
																	 });
			encoder->BindResources(cameraBinding);

			DrawItemRenderer::RenderCategory(*encoder, ctx, {
				.Category = DrawCategory::Opaque,
				.RenderMode = ViewportRenderMode::Wireframe
											 });

			DrawItemRenderer::RenderCategory(*encoder, ctx, {
				.Category = DrawCategory::AlphaMasked,
				.RenderMode = ViewportRenderMode::Wireframe
											 });
		}
	};
}