module Zephyr.Renderer.DrawItemRenderer;

import Zephyr.Renderer.RHI.Device;

namespace Zephyr
{
	void DrawItemRenderer::RenderCategory(
		RHI::IRenderPassEncoder& encoder,
		const PassExecutionContext& ctx,
		const DrawItemExecutionConfig& config)
	{
		auto items = ctx.Queue.GetCategory(config.Category);

		if (items.empty())
			return;

		const Material* currentMaterial = nullptr;
		Ref<RHI::IPipeline> currentPipeline = nullptr;

		for (const auto& item : items)
		{
			if (item.Material.get() != currentMaterial)
			{
				currentMaterial = item.Material.get();

				RHI::GraphicsPipelineDesc pipelineDesc{};
				pipelineDesc.Shader = currentMaterial->GetShader();

				ConfigurePipeline(pipelineDesc, config);

				currentPipeline = RHI::Device::CreatePipeline(pipelineDesc);
				encoder.BindPipeline(currentPipeline);
				encoder.BindResources(currentMaterial->GetBindings());
			}

			RenderItem(encoder, item, ctx);
		}
	}

	void DrawItemRenderer::ConfigurePipeline(RHI::GraphicsPipelineDesc& desc, const DrawItemExecutionConfig& config)
	{
		// Default settings based on category
		switch (config.Category)
		{
		case DrawCategory::Opaque:
		case DrawCategory::AlphaMasked:
			desc.Depth.DepthTestEnable = true;
			desc.Depth.DepthWriteEnable = true;
			desc.Blend.Enable = false;
			desc.Rasterizer.Cull = RHI::CullMode::Back;
			break;

		case DrawCategory::Transparent:
			desc.Depth.DepthTestEnable = true;
			desc.Depth.DepthWriteEnable = false;
			desc.Blend.Enable = true;
			desc.Rasterizer.Cull = RHI::CullMode::None;
			break;

		case DrawCategory::Overlay:
			desc.Depth.DepthTestEnable = false;
			desc.Depth.DepthWriteEnable = false;
			desc.Blend.Enable = true;
			desc.Rasterizer.Cull = RHI::CullMode::None;
			break;
		}

		// Apply render mode
		switch (config.RenderMode)
		{
		case ViewportRenderMode::Wireframe:
			desc.Rasterizer.Polygon = RHI::PolygonMode::Wireframe;
			desc.Depth.DepthTestEnable = true;
			desc.Depth.DepthWriteEnable = false;
			break;

		default:
			desc.Rasterizer.Polygon = RHI::PolygonMode::Fill;
			break;
		}
	}

	void DrawItemRenderer::RenderItem(RHI::IRenderPassEncoder & encoder, const DrawItem & item, const PassExecutionContext & ctx)
	{
		ObjectUniformData objectData{ .Model = item.Transform };
		ctx.Resources.ObjectBuffer->SetData(
			std::as_bytes(std::span{ &objectData, 1 })
		);

		auto objectBinding = std::to_array<RHI::ResourceBinding>({
			{ RHI::UniformBindings::PerObject, ctx.Resources.ObjectBuffer }
																 });
		encoder.BindResources(objectBinding);

		encoder.BindVertexArray(item.Mesh->GetVertexArray());
		if (item.Mesh->GetIndexCount() > 0)
			encoder.DrawIndexed(item.Mesh->GetIndexCount());
		else
			encoder.Draw(item.Mesh->GetVertexCount());
	}
}