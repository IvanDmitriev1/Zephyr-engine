export module Zephyr.Renderer.OpenGL.GlBuffers;

export import Zephyr.Renderer.Core.IBuffer;
export import Zephyr.Renderer.OpenGL.GlBuffer;

export namespace Zephyr::RHI::OpenGL
{
    template <class IBufferInterface>
    class GlBufferWrapper : public IBufferInterface
    {
    protected:
        explicit GlBufferWrapper(BufferDesc desc)
            : m_Buffer(std::move(desc))
        {}

    public:
        const BufferDesc& GetDesc() const noexcept override
        {
            return m_Buffer.GetDesc();
        }

        void SetData(std::span<const std::byte> data, uint64_t dstOffsetBytes) override
        {
            m_Buffer.SetData(data, dstOffsetBytes);
        }

        const GlBuffer& GetUnderlyingBuffer() const noexcept
        {
            return m_Buffer;
        }

    protected:
        GlBuffer m_Buffer;
    };

    class GlVertexBuffer final : public GlBufferWrapper<IVertexBuffer>
    {
    public:
        explicit GlVertexBuffer(BufferDesc desc)
            : GlBufferWrapper<IVertexBuffer>(desc)
        {
            if (!HasFlag(desc.Usage, BufferUsage::Vertex))
                throw std::runtime_error("GlVertexBuffer: desc.Usage must include BufferUsage::Vertex");
        }
    };

    class GlIndexBuffer final : public GlBufferWrapper<IIndexBuffer>
    {
    public:
        explicit GlIndexBuffer(IndexBufferDesc desc)
            : GlBufferWrapper<IIndexBuffer>(desc.ToBufferDesc()),
            m_Type(desc.Type),
            m_Count(desc.SizeBytes / GetIndexSize(desc.Type))
        {
            if (!HasFlag(desc.Usage, BufferUsage::Index))
                throw std::runtime_error("GlIndexBuffer: desc.Usage must include BufferUsage::Index");
        }

        IndexType GetIndexType() const noexcept override
        {
            return m_Type;
        }

        uint32_t GetCount() const noexcept override
        {
            return m_Count;
        }

    private:
        IndexType m_Type;
        uint32_t m_Count{};
    };

    class GLUniformBuffer final : public GlBufferWrapper<IUniformBuffer>
    {
    public:
        explicit GLUniformBuffer(BufferDesc desc)
            : GlBufferWrapper<IUniformBuffer>(desc)
        {
            if (!HasFlag(desc.Usage, BufferUsage::Uniform))
                throw std::runtime_error("GLUniformBuffer: desc.Usage must include BufferUsage::Uniform");
        }
    };
}