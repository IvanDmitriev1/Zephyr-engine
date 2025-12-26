export module Zephyr.Renderer.Core.IBuffer;

export import Zephyr.Renderer.Resources.BufferTypes;

export namespace Zephyr::RHI
{
    class IVertexBuffer 
    {
    public:
        virtual ~IVertexBuffer() = default;

    public:
        virtual const BufferDesc& GetDesc() const noexcept = 0;
        virtual void SetData(std::span<const std::byte> data, uint64_t dstOffsetBytes = 0) = 0;
    };

    class IIndexBuffer
    {
    public:
        virtual ~IIndexBuffer() = default;

    public:
        virtual const BufferDesc& GetDesc() const noexcept = 0;
        virtual uint32_t GetCount() const noexcept = 0;
        virtual IndexType GetIndexType() const noexcept = 0;

        virtual void SetData(std::span<const std::byte> data, uint64_t dstOffsetBytes = 0) = 0;
    };

    class IUniformBuffer
    {
    public:
        virtual ~IUniformBuffer() = default;

    public:
        virtual const BufferDesc& GetDesc() const noexcept = 0;
        virtual void SetData(std::span<const std::byte> data, uint64_t dstOffsetBytes = 0) = 0;
    };
}