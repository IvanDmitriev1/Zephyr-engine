module Zephyr.Renderer.Passes.DepthPrepass;

import Zephyr.Renderer.RHI.Device;
import Zephyr.Renderer.DrawItemRenderer;

namespace Zephyr
{
	void DepthPrepass::Execute(PassExecutionContext& ctx)
	{
		RHI::RenderPassDesc passDesc
		{
			.Target = ctx.Target,
			.Colors = std::to_array<RHI::ColorAttachment>(
			{
				{.Load = RHI::LoadOp::DontCare, .Store = RHI::StoreOp::DontCare, },
			}),
			.Depth = RHI::DepthAttachment
			{
				.Load = RHI::LoadOp::Clear,
				.Store = RHI::StoreOp::Store,
				.ClearDepth = 1.0f,
				.DepthTestEnable = true,
				.DepthWriteEnable = true
			},
			.DebugName = "DepthPass"
		};

		auto encoder = RHI::Device::CreateRenderPassEncoder(passDesc);

		auto cameraBinding = std::to_array<RHI::ResourceBinding>({
			{ RHI::UniformBindings::Camera, ctx.Resources.CameraBuffer }
																 });
		encoder->BindResources(cameraBinding);

		DrawItemRenderer::RenderCategory(*encoder, ctx, {
			.Depth = *passDesc.Depth,
			.Category = DrawCategory::Opaque,
			.RenderMode = ctx.RenderMode
										 });

	}
}