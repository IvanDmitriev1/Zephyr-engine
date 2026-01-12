export module Zephyr.Renderer.SceneRenderer;

export import Zephyr.Renderer.Resources.RendererTypes;
export import Zephyr.Renderer.Core.IFrameBuffer;

import Zephyr.Renderer.Core.IRenderPassEncoder;
import Zephyr.Renderer.Core.IBuffer;

export namespace Zephyr
{
	class SceneRenderer final
	{
	public:
		SceneRenderer();
		~SceneRenderer() = default;

	public:
		void Submit(const DrawItem& item);
		void Submit(std::span<const DrawItem> items);

		void BeginFrame(const CameraUniformData& cameraData);
		void ExecutePass(const RHI::RenderPassDesc& passDesc);

	private:
		void SortQueues();
		void ConfigureRenderQueue(RHI::IRenderPassEncoder* encoder, RenderQueue queueType);
		void ConfigurePipelineForQueue(RHI::GraphicsPipelineDesc& desc, RenderQueue queue, AlphaMode alphaMode);

	private:
		RenderQueueArray<std::vector<DrawItem>> m_Queues;

		Ref<RHI::IBuffer> m_CameraUniformBuffer;
		Ref<RHI::IBuffer> m_ObjectUniformBuffer;
	};
}