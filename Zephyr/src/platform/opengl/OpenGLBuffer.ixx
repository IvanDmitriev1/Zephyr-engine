export module zephyr.opengl.OpenGLBuffer;

export import zephyr.renderer.IBuffer;
import std.compat;

export namespace zephyr
{
    class OpenGLBuffer final : public IBuffer
    {
    public:
        explicit OpenGLBuffer(const BufferCreateInfo& info);
        ~OpenGLBuffer() override;

    public:
        BufferType GetType() const override
        {
            return m_Type;
        }
        BufferUsage GetUsage() const override
        {
            return m_Usage;
        }
        size_t GetSize() const override
        {
            return m_Size;
        }

        uint32_t GetRendererID() const
        {
            return m_RendererID;
        }

        void SetData(const void* data, size_t size, size_t offset = 0) override;

        void Bind() const override;
        void Unbind() const override;
        
    private:
        uint32_t GetGLTarget() const;
        uint32_t GetGLUsage() const;

    private:
        uint32_t      m_RendererID = 0;
        BufferType  m_Type;
        BufferUsage m_Usage;
        std::size_t m_Size = 0;
    };
}