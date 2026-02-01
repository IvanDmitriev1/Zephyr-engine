module Zephyr.Renderer.Passes.GBufferPass;

import Zephyr.Renderer.RHI.Device;
import Zephyr.Renderer.DrawBatch;

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
			},
			.DebugName = "ForwardPass"
		};

		auto cmdBuffer = RHI::Device::CreateCommandBuffer();
		
		{
			auto encoder = cmdBuffer->BeginRenderPass(passDesc);

			auto forwardConfig = [](RHI::GraphicsPipelineDesc& desc)
			{
				desc.Depth.DepthTestEnable = true;
				desc.Depth.DepthWriteEnable = false;  // Read depth from prepass
			};

			DrawBatch::SubmitCategory(*encoder, ctx, DrawCategory::Opaque, forwardConfig);
			DrawBatch::SubmitCategory(*encoder, ctx, DrawCategory::AlphaMasked, forwardConfig);
		}

		cmdBuffer->Execute();
	}
}