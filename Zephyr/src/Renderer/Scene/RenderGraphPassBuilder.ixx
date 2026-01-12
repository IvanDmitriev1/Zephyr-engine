export module Zephyr.Renderer.RenderGraphPassBuilder;

export import Zephyr.Renderer.RenderGraphPass;

export namespace Zephyr
{
	class RenderGraphPassBuilder
	{
	public:
		RenderGraphPassBuilder(RenderGraphPass& pass);
		~RenderGraphPassBuilder() = default;

	public:
		RenderGraphPassBuilder& ClearColor(float r, float g, float b, float a = 1.0f);
		RenderGraphPassBuilder& LoadColor();
		RenderGraphPassBuilder& DontCareColor();

		RenderGraphPassBuilder& ClearDepth(float depth = 1.0f);
		RenderGraphPassBuilder& LoadDepth();
		RenderGraphPassBuilder& NoDepth();
		RenderGraphPassBuilder& StoreDepth();

		RenderGraphPassBuilder& OnlyGeometry();
		RenderGraphPassBuilder& OnlyTransparent();
		RenderGraphPassBuilder& Execute(RenderGraphPass::ExecuteFunc&& func);


	private:
		RenderGraphPass& m_Pass;
	};
}