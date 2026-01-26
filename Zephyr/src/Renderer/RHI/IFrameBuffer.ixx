export module Zephyr.Renderer.RHI.IFrameBuffer;

export import Zephyr.Renderer.RHI.FrameBufferTypes;
export import Zephyr.Renderer.RHI.ITexture;
export import Zephyr.Core.CoreTypes;

export namespace Zephyr::RHI
{
    class IFrameBuffer
    {
    public:
        virtual ~IFrameBuffer() = default;

    public:
        virtual const FrameBufferDesc& GetDesc() const noexcept = 0;

        virtual size_t GetColorAttachmentCount() const noexcept = 0;
        virtual const ITexture& GetColorAttachment(size_t index) const = 0;
        virtual std::optional<std::reference_wrapper<const ITexture>> GetDepthAttachment() const = 0;

        virtual void Resize(Extent2D newSize) = 0;
    };
}