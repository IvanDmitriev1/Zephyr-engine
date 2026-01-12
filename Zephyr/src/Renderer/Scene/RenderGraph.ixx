export module Zephyr.Renderer.RenderGraph;

export import Zephyr.Renderer.RenderGraphPassBuilder;

export namespace Zephyr
{
	class RenderGraph final
	{
	public:
		RenderGraph() = default;
		~RenderGraph() = default;

	public:
		RenderGraphPassBuilder AddPass(std::string name, Ref<RHI::IFrameBuffer> target);
		void Execute(SceneRenderer& renderer);
		void Clear();

	private:
		std::vector<RenderGraphPass> m_Passes{};
	};
}