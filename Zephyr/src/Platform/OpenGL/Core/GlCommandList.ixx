export module Zephyr.Renderer.OpenGL.GlCommandList;

export import Zephyr.Renderer.Core.ICommandList;

export namespace Zephyr::RHI::OpenGL
{
	class GlCommandList final : public ICommandList
	{
	public:
		GlCommandList() = default;
		~GlCommandList() override = default;

	public:
		// Render pass
		void BeginRenderPass(const RenderPassDesc& rp) override;
		void EndRenderPass() override;

		// Pipeline binding
		void BindPipeline(const Ref<IPipeline>& pipeline) override;

		// Resource binding
		void BindVertexArray(const Ref<IVertexArray>& vao) override;

		void BindResources(std::span<ResourceBinding> bindings) override;

		// Draw commands
		void Draw(uint32_t vertexCount, uint32_t firstVertex) override;
		void DrawIndexed(uint32_t indexCount, uint32_t firstIndex) override;

	private:
		uint32_t GetCurrentShaderProgram() const;

	private:
		bool m_IsInRenderPass{};

		Ref<IPipeline> m_BoundedPipeline{};
		Ref<IVertexArray> m_BoundedVao{};
	};
}