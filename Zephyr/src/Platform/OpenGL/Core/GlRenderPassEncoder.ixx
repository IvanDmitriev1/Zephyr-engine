export module Zephyr.Renderer.OpenGL.GlRenderPassEncoder;

export import Zephyr.Renderer.RHI.Interfaces.IRenderEncoder;
export import Zephyr.Renderer.RHI.Types.RenderPassTypes;
export import Zephyr.Renderer.OpenGL.GlPipeline;

export namespace Zephyr::RHI::OpenGL
{
	class GlRenderPassEncoder final : public IRenderEncoder
	{
	public:
		explicit GlRenderPassEncoder(const RenderPassDesc& desc);
		~GlRenderPassEncoder() override;

	public:
		void BindPipeline(const Ref<IPipeline>& pipeline) override;
		void BindVertexArray(const Ref<IVertexArray>& vao) override;
		void BindResources(std::span<const ResourceBinding> bindings) override;

		// Draw commands
		void Draw(uint32_t vertexCount, uint32_t firstVertex) override;
		void DrawIndexed(uint32_t indexCount, uint32_t firstIndex) override;

	private:
		Ref<IFrameBuffer> m_Framebuffer;

		Ref<IPipeline> m_CurrentPipeline;
		Ref<IVertexArray> m_BoundedVao{};
	};
}