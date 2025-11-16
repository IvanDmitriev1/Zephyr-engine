export module zephyr.opengl.OpenGLVertexArray;

export import zephyr.renderer.IVertexArray;
export import zephyr.opengl.OpenGLBuffer;

export namespace zephyr
{
    class OpenGLVertexArray final : public IVertexArray
    {
    public:
        explicit OpenGLVertexArray(const VertexArrayCreateInfo& info);
        ~OpenGLVertexArray() override;

    public:
        void Bind() const override;
        void Unbind() const override;

        const Ref<IBuffer>& GetVertexBuffer() const override
        {
            return m_VertexBuffer;
        }
        const Ref<IBuffer>& GetIndexBuffer() const override
        {
            return m_IndexBuffer;
        }

        uint32_t GetIndexCount() const override
        {
            return m_IndexCount;
        }
        IndexType GetIndexType() const override
        {
            return m_IndexType;
        }

    private:
        void SetVertexBuffer();
		void SetIndexBuffer();
        void ConfigureVertexAttributes(const OpenGLBuffer& glVertexBuffer);

    private:
        uint32_t m_RendererID{};

        const Ref<IBuffer> m_VertexBuffer;
        const Ref<IBuffer> m_IndexBuffer;

        const VertexLayout m_Layout;
        const IndexType m_IndexType;
        uint32_t m_IndexCount{};
    };
}