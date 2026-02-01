module Zephyr.Renderer.Passes.DepthPrepass;

import Zephyr.Renderer.RHI.Device;
import Zephyr.Renderer.DrawBatch;

namespace Zephyr
{
	void DepthPrepass::Execute(PassExecutionContext& ctx)
	{
		RHI::RenderPassDesc passDesc
		{
			.Target = ctx.Target,
			.Colors = {},
			.Depth = RHI::DepthAttachment
			{
				.Load = RHI::LoadOp::Clear,
				.Store = RHI::StoreOp::Store,
				.ClearDepth = 1.0f,
			},
			.DebugName = "DepthPass"
		};

		auto cmdBuffer = RHI::Device::CreateCommandBuffer();
		
		{
			auto encoder = cmdBuffer->BeginRenderPass(passDesc);

			auto cameraBinding = std::to_array<RHI::ResourceBinding>({
				{ RHI::UniformBindings::Camera, ctx.Resources.CameraBuffer }
																	 });
			encoder->BindResources(cameraBinding);

			DrawBatch::SubmitCategory(*encoder, ctx, DrawCategory::Opaque,
									  [](RHI::GraphicsPipelineDesc& desc)
			{
				desc.ColorFormat = {};
			});
		}

		cmdBuffer->Execute();
	}
}