export module Zephyr.Renderer.Core.IBuffer;

export import Zephyr.Renderer.Resources.BufferTypes;

export namespace Zephyr::RHI
{
    class IBuffer
    {
    public:
        virtual ~IBuffer() = default;

        virtual const BufferDesc& GetDesc() const noexcept = 0;
    };

    class IVertexBuffer : public IBuffer
    {
    public:
    };

    class IIndexBuffer : public IBuffer
    {
    public:
        virtual uint32_t GetCount() const = 0;
    };

    class IUniformBuffer : public IBuffer
    {
    };
}