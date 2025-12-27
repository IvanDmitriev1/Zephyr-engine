export module Zephyr.Renderer.OpenGL.GlCommandList;

export import Zephyr.Renderer.Core.ICommandList;

export namespace Zephyr::RHI::OpenGL
{
	class GlCommandList final : public ICommandList
	{
	public:
		void Begin() override;
		void End() override;

		// Render pass
		void BeginRenderPass(const RenderPassDesc& rp) override;
		void EndRenderPass() override;

		// Pipeline binding
		void BindPipeline(const Ref<IPipeline>& pipeline) override;

		// Resource binding
		void BindVertexArray(const Ref<IVertexArray>& vao) override;

		// Dynamic state
		void SetViewport(float x, float y, float w, float h) override;
		void SetScissor(int32_t x, int32_t y, uint32_t w, uint32_t h) override;

		// Draw commands
		void Draw(uint32_t vertexCount, uint32_t firstVertex) override;
		void DrawIndexed(uint32_t indexCount, uint32_t firstIndex) override;

	private:
		bool m_IsInRenderPass{};

		Ref<IPipeline> m_BoundedPipeline{};
		Ref<IVertexArray> m_BoundedVao{};
	};
}