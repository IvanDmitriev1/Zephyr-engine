module Zephyr.Renderer.Graph.Passes.WireframeOverlayPass;

import Zephyr.Renderer.RHI.Interfaces.Device;
import Zephyr.Renderer.Graph.DrawBatch;

namespace Zephyr
{
	void WireframeOverlayPass::Execute(PassExecutionContext& ctx)
	{
		if (ctx.RenderMode != ViewportRenderMode::Wireframe)
			return;

		auto colorAttachments = std::to_array<RHI::ColorAttachment>(
		{
			{
				.Load = RHI::LoadOp::Clear,
				.Store = RHI::StoreOp::Store,
				.Clear = {0.1f, 0.1f, 0.15f, 1.0f}
			}
		});

		RHI::RenderPassDesc passDesc{
			.Target = ctx.Target,
			.Colors = colorAttachments,
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