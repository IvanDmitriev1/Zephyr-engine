export module Zephyr.Renderer.OpenGL.GlRenderPassEncoder;

export import Zephyr.Renderer.Core.IRenderPassEncoder;

export namespace Zephyr::RHI::OpenGL
{
	class GlRenderPassEncoder final : public IRenderPassEncoder
	{
	public:
		explicit GlRenderPassEncoder(const RenderPassDesc& rp);
		~GlRenderPassEncoder() override;

	public:
		void BindPipeline(const Ref<IPipeline>& pipeline) override;
		void BindVertexArray(const Ref<IVertexArray>& vao) override;
		void BindResources(std::span<const ResourceBinding> bindings) override;

		// Draw commands
		void Draw(uint32_t vertexCount, uint32_t firstVertex) override;
		void DrawIndexed(uint32_t indexCount, uint32_t firstIndex) override;

	private:
		uint32_t GetCurrentShaderProgram() const;

	private:
		Ref<IPipeline> m_BoundedPipeline{};
		Ref<IVertexArray> m_BoundedVao{};
	};
}