export module Zephyr.Renderer.Core.IFrameBuffer;

export import Zephyr.Renderer.Resources.FrameBufferTypes;
export import Zephyr.Renderer.Core.ITexture;
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

        virtual void Resize(glm::ivec2 newSize) = 0;
    };
}