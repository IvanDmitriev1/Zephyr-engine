export module Zephyr.Renderer.RHI.Interfaces.IFrameBuffer;

import Zephyr.Renderer.RHI.Types.FrameBufferTypes;
import Zephyr.Renderer.RHI.Interfaces.ITexture;
import Zephyr.Core.CoreTypes;

export namespace Zephyr::RHI
{
    class IFrameBuffer
    {
    public:
        virtual ~IFrameBuffer() = default;

    public:
		virtual Extent2D GetSize() const noexcept = 0;
        virtual size_t GetColorAttachmentCount() const noexcept = 0;
        virtual const ITexture& GetColorAttachment(size_t index) const = 0;
        virtual std::optional<std::reference_wrapper<const ITexture>> GetDepthAttachment() const = 0;

        virtual void Resize(Extent2D newSize) = 0;
    };
}
