module Zephyr.Renderer.BaseGeometryPass;

import Zephyr.Renderer.RHI.Device;

namespace Zephyr
{
	void BaseGeometryPass::RenderPhases(
		RHI::IRenderPassEncoder& encoder,
		const PassExecutionContext& context,
		std::span<const DrawCategory> categoryToRender)
	{
		const Material* currentMaterial = nullptr;
		Ref<RHI::IPipeline> currentPipeline = nullptr;

		for (DrawCategory category : categoryToRender)
		{
			auto items = context.Queue.GetCategory(category);

			for (const auto& item : items)
			{
				if (item.Material.get() != currentMaterial)
				{
					currentMaterial = item.Material.get();

					RHI::GraphicsPipelineDesc pipelineDesc{};
					pipelineDesc.Shader = currentMaterial->GetShader();
					ConfigurePipelineForPhase(pipelineDesc, category);

					currentPipeline = RHI::Device::CreatePipeline(pipelineDesc);
					encoder.BindPipeline(currentPipeline);
					encoder.BindResources(currentMaterial->GetBindings());
				}

				ObjectUniformData objectData{ .Model = item.Transform };
				context.Resources.ObjectBuffer->SetData(
					std::as_bytes(std::span{ &objectData, 1 })
				);

				auto objectBinding = std::to_array<RHI::ResourceBinding>({
					{ RHI::UniformBindings::PerObject, context.Resources.ObjectBuffer }
																		 });
				encoder.BindResources(objectBinding);

				// Draw
				encoder.BindVertexArray(item.Mesh->GetVertexArray());
				if (item.Mesh->GetIndexCount() > 0)
					encoder.DrawIndexed(item.Mesh->GetIndexCount());
				else
					encoder.Draw(item.Mesh->GetVertexCount());
			}
		}
	}

	void BaseGeometryPass::ConfigurePipelineForPhase(RHI::GraphicsPipelineDesc& desc, DrawCategory category)
	{
		desc.Depth.DepthTestEnable = true;
		desc.Depth.DepthWriteEnable = true;
		desc.Blend.Enable = false;

		switch (category)
		{
		case DrawCategory::Transparent:
			desc.Blend.Enable = true;
			desc.Depth.DepthWriteEnable = false; // Don't write depth for transparents
			break;

		case DrawCategory::Overlay:
			desc.Depth.DepthTestEnable = false; // Always on top
			desc.Depth.DepthWriteEnable = false;
			break;

		default:
			break;
		}
	}
}