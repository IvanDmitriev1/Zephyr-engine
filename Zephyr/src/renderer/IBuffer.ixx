export module zephyr.renderer.IBuffer;

export import zephyr.core.coreTypes;
import std.compat;

export namespace zephyr
{
    enum class BufferType : uint8_t
    {
        Vertex,
        Index,
        Uniform,
        Storage
    };

    enum class BufferUsage : uint8_t
    {
        StaticDraw,   // written once, read many times
        DynamicDraw,  // updated frequently
        StreamDraw    // updated every frame
    };

    struct BufferCreateInfo
    {
        BufferType Type{};
        BufferUsage Usage = BufferUsage::StaticDraw;
        size_t Size{};
        const void* Data = nullptr;
    };

    class IBuffer
    {
    public:
		IBuffer() = default;
        virtual ~IBuffer() = default;

        IBuffer(const IBuffer&) = delete;
        IBuffer& operator=(const IBuffer&) = delete;

    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetData(
            const void* data,
            size_t size,
            size_t offset = 0) = 0;

        virtual size_t GetSize() const = 0;
        virtual BufferUsage GetUsage() const = 0;
        virtual BufferType GetType() const = 0;

        // Factory – implemented per backend
        static std::shared_ptr<IBuffer> Create(const BufferCreateInfo& info);
    };
}