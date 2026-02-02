export module Zephyr.Renderer.RHI.FrameBufferTypes;

export import Zephyr.Renderer.RHI.TextureTypes;

export namespace Zephyr::RHI
{
    struct FrameBufferDesc
    {
		Extent2D Size{};
		std::span<const TextureFormat> ColorFormats{};
		std::optional<TextureFormat> DepthFormat{};
		uint32_t SampleCount = 1;  // MSAA

		std::string_view DebugName = "FrameBuffer";
    };
}