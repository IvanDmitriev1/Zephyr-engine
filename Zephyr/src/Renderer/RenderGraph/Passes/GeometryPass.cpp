module Zephyr.Renderer.Passes.GeometryPass;

import Zephyr.Renderer.RHI.Device;

namespace Zephyr
{
	void GeometryPass::Execute(PassExecutionContext& ctx)
	{
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

		RenderPhases(*encoder, ctx, std::to_array<RenderPhase>({
			RenderPhase::Background,
				RenderPhase::Geometry,
				RenderPhase::AlphaTest
					 }));
	}
}