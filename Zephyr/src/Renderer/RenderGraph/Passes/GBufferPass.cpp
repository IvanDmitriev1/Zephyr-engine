module Zephyr.Renderer.Passes.GBufferPass;

import Zephyr.Renderer.RHI.Device;
import Zephyr.Renderer.DrawItemRenderer;

namespace Zephyr
{
	void GBufferPass::Execute(PassExecutionContext& ctx)
	{
		if (ctx.RenderMode == ViewportRenderMode::Wireframe)
			return;

		const Extent2D targetSize = ctx.Target->GetDesc().Size;
		m_GBuffer.EnsureSize(targetSize);

		RHI::RenderPassDesc passDesc
		{
			.Target = ctx.Target,
			.Colors = std::to_array<RHI::ColorAttachment>(
			{
				{.Load = RHI::LoadOp::Clear, .Store = RHI::StoreOp::Store, .Clear = {0.1f, 0.1f, 0.15f, 1.0f} },

			}),
			.Depth = RHI::DepthAttachment{.Load = RHI::LoadOp::Clear, .Store = RHI::StoreOp::DontCare, .ClearDepth = 1.0f },
			.DebugName = "GeometryPass"
		};

		auto encoder = RHI::Device::CreateRenderPassEncoder(passDesc);

		auto cameraBinding = std::to_array<RHI::ResourceBinding>({
			{ RHI::UniformBindings::Camera, ctx.Resources.CameraBuffer }
																 });
		encoder->BindResources(cameraBinding);


		DrawItemRenderer::RenderCategory(*encoder, ctx, {
			.Category = DrawCategory::Opaque,
			.RenderMode = ctx.RenderMode
										 });

		DrawItemRenderer::RenderCategory(*encoder, ctx, {
			.Category = DrawCategory::AlphaMasked,
			.RenderMode = ctx.RenderMode
										 });
	}
}