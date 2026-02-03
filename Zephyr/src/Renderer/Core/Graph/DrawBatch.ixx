export module Zephyr.Renderer.Graph.DrawBatch;

export import Zephyr.Renderer.RHI.Interfaces.IRenderEncoder;
export import Zephyr.Renderer.Resources.PipelineCache;
export import Zephyr.Renderer.Types.RenderGraphTypes;
export import Zephyr.Renderer.Types.RendererTypes;

export namespace Zephyr
{
	class DrawBatch final
	{
	public:
		static void Submit(
			RHI::IRenderEncoder& encoder,
			const DrawItem& item,
			const PassExecutionContext& ctx);

		template<GraphicsPipelineConfigurator ConfigFn>
		static void SubmitCategory(
			RHI::IRenderEncoder& encoder,
			const PassExecutionContext& ctx,
			DrawCategory category,
			ConfigFn&& pipelineConfig);
	};

	template<GraphicsPipelineConfigurator ConfigFn>
	void DrawBatch::SubmitCategory(RHI::IRenderEncoder& encoder, const PassExecutionContext& ctx, DrawCategory category, ConfigFn&& pipelineConfig)
	{
		auto& cache = PipelineCache::Get();
		const Material* currentMaterial = nullptr;

		for (const auto& item : ctx.Queue.GetCategory(category))
		{
			if (item.Material.get() != currentMaterial)
			{
				currentMaterial = item.Material.get();

				auto pipeline = cache.GetOrCreate(
					*currentMaterial,
					ctx.Target,
					pipelineConfig);

				encoder.BindPipeline(pipeline);
				encoder.BindResources(currentMaterial->GetBindings());
			}

			Submit(encoder, item, ctx);
		}
	}
	void DrawBatch::Submit(RHI::IRenderEncoder& encoder, const DrawItem& item, const PassExecutionContext& ctx)
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
