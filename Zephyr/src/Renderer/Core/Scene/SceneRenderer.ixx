export module Zephyr.Renderer.Scene.SceneRenderer;

export import Zephyr.Renderer.Types.RendererTypes;
export import Zephyr.Renderer.RHI.Interfaces.IFrameBuffer;
export import Zephyr.Renderer.Graph.RenderGraph;
export import Zephyr.Scene.World;

export namespace Zephyr
{
	class SceneRenderer final
	{
	public:
		explicit SceneRenderer(World& world);
		~SceneRenderer() = default;

		void BeginFrame();
		void Execute(Ref<RHI::IFrameBuffer> target, ViewportRenderMode renderMode);

		void RenderWorld(Entity cameraEntity);

		void Submit(const DrawItem& item);
		void Submit(std::span<const DrawItem> items);

		inline RenderGraph& GetRenderGraph() { return m_Graph; }

	private:
		CameraUniformData ExtractCameraData(Entity cameraEntity);

	private:
		World& m_World;
		RenderQueue m_Queue;
		RenderGraph m_Graph;
		RenderResources m_Resources;
	};
}