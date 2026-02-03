export module Zephyr.Renderer.OpenGL.GlVertexArray;

export import Zephyr.Renderer.RHI.Interfaces.IVertexArray;
import std.compat;

export namespace Zephyr::RHI::OpenGL
{
	class GlVertexArray final : public IVertexArray
	{
	public:
		explicit GlVertexArray(VertexArrayCreateInfo createInfo);
		~GlVertexArray() override;

	public:
		const VertexLayout& GetLayout() const noexcept override { return m_Layout; }
		const Zephyr::Ref<IBuffer>& GetVertexBuffer() const noexcept override { return m_VertexBuffer; }
		const std::optional<IndexBinding>& GetIndexBinding() const noexcept override { return m_IndexBinding; }

	public:
		void Bind();

	private:
		void BindVertexBuffer();
		void ConfigureVertexAttributes();
		void BindIndexBuffer();

	private:
		uint32_t m_RendererID = 0;

		const VertexLayout m_Layout;
		const Ref<IBuffer> m_VertexBuffer;
		const std::optional<IndexBinding> m_IndexBinding;
	};
}