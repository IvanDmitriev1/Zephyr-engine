export module Zephyr.Renderer.Resources.FrameBufferTypes;

export import Zephyr.Renderer.Resources.TextureTypes;

export namespace Zephyr::RHI
{
    struct FrameBufferAttachmentDesc
    {
        TextureFormat Format = TextureFormat::RGBA8;
    };

    struct FrameBufferDesc
    {
		Extent2D Size{};
        std::vector<FrameBufferAttachmentDesc> ColorAttachments{};
        std::optional<FrameBufferAttachmentDesc> DepthStencilAttachment{};

        std::string_view DebugName = "FrameBuffer";
    };
}