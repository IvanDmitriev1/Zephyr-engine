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
				{
					.Load = RHI::LoadOp::Clear,
					.Store = RHI::StoreOp::Store,
					.Clear = {0.1f, 0.1f, 0.15f, 1.0f}
				},
			}),
			.Depth = RHI::DepthAttachment
			{
				.Load = RHI::LoadOp::Load,
				.Store = RHI::StoreOp::Store,
				.DepthTestEnable = true,
				.DepthWriteEnable = false
			},
			.DebugName = "ForwardPass"
		};

		auto encoder = RHI::Device::CreateRenderPassEncoder(passDesc);

		DrawItemRenderer::RenderCategory(*encoder, ctx, {
			.Depth = *passDesc.Depth,
			.Category = DrawCategory::Opaque,
			.RenderMode = ctx.RenderMode
										 });

		DrawItemRenderer::RenderCategory(*encoder, ctx, {
			.Depth = *passDesc.Depth,
			.Category = DrawCategory::AlphaMasked,
			.RenderMode = ctx.RenderMode
										 });
	}
}