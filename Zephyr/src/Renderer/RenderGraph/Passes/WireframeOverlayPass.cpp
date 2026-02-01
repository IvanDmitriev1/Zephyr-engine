module Zephyr.Renderer.Passes.WireframeOverlayPass;

import Zephyr.Renderer.RHI.Device;
import Zephyr.Renderer.DrawBatch;

namespace Zephyr
{
	void WireframeOverlayPass::Execute(PassExecutionContext& ctx)
	{
		if (ctx.RenderMode != ViewportRenderMode::Wireframe)
			return;

		RHI::RenderPassDesc passDesc{
			.Target = ctx.Target,
			.Colors = std::to_array<RHI::ColorAttachment>({
				{
					.Load = RHI::LoadOp::Clear,
					.Store = RHI::StoreOp::Store,
					.Clear = {0.0f, 0.0f, 0.0f, 1.0f}
				}
			}),
			.Depth = RHI::DepthAttachment{
				.Load = RHI::LoadOp::Load,
				.Store = RHI::StoreOp::Store,
				.ClearDepth = 1.0f,
			},
			.DebugName = "WireframeOverlayPass"
		};

		auto cmdBuffer = RHI::Device::CreateCommandBuffer();
		
		{
			auto encoder = cmdBuffer->BeginRenderPass(std::move(passDesc));

			auto cameraBinding = std::to_array<RHI::ResourceBinding>({
				{ RHI::UniformBindings::Camera, ctx.Resources.CameraBuffer }
																	 });
			encoder->BindResources(cameraBinding);

			auto wireframeConfig = [](RHI::GraphicsPipelineDesc& desc)
			{
				desc.Rasterizer.Polygon = RHI::PolygonMode::Wireframe;
				desc.Rasterizer.Cull = RHI::CullMode::None;
				desc.Depth.DepthTestEnable = true;
				desc.Depth.DepthWriteEnable = false;
			};

			DrawBatch::SubmitCategory(*encoder, ctx, DrawCategory::Opaque, wireframeConfig);
			DrawBatch::SubmitCategory(*encoder, ctx, DrawCategory::AlphaMasked, wireframeConfig);
		}

		cmdBuffer->Execute();
	}
}