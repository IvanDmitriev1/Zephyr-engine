export module Zephyr.Renderer.OpenGL.GlVertexArray;

export import Zephyr.Renderer.Core.IVertexArray;

export namespace Zephyr::RHI::OpenGL
{
	class GlVertexArray final : public IVertexArray
	{
	public:
		explicit GlVertexArray(VertexArrayCreateInfo createInfo);
		~GlVertexArray() override;

	public:
		const VertexLayout& GetLayout() const noexcept override
		{
			return m_Layout;
		}
		const Zephyr::Ref<IVertexBuffer>& GetVertexBuffer() const noexcept override
		{
			return m_VertexBuffer;
		}
		const Zephyr::Ref<IIndexBuffer>& GetIndexBuffer() const noexcept override
		{
			return m_IndexBuffer;
		}
		bool HasIndexBuffer() const noexcept override
		{
			return (bool)m_IndexBuffer;
		}

		uint32_t GetRendererID() const noexcept
		{
			return m_RendererID;
		}

	private:
		void BindVertexBuffer();
		void ConfigureVertexAttributes();
		void BindIndexBuffer();

	private:
		uint32_t m_RendererID = 0;
		Ref<IVertexBuffer> m_VertexBuffer;
		Ref<IIndexBuffer>  m_IndexBuffer;
		VertexLayout m_Layout;
	};
}