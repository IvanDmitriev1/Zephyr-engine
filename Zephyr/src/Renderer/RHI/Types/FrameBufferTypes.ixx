export module Zephyr.Renderer.RHI.Types.FrameBufferTypes;

import Zephyr.Renderer.RHI.Types.TextureTypes;

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
