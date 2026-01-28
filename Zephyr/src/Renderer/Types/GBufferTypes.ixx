export module Zephyr.Renderer.Types.GBufferTypes;

export import Zephyr.Renderer.RHI.TextureTypes;
export import Zephyr.Renderer.RHI.IFrameBuffer;
export import Zephyr.Core.CoreTypes;

export namespace Zephyr
{
	enum class GBufferAttachment : uint8_t
	{
		AlbedoMetallic = 0,
		NormalRoughness,
		EmissiveAO,
		Depth
	};

	struct GBufferDesc
	{
		Extent2D Size{};
		RHI::TextureFormat AlbedoFormat = RHI::TextureFormat::RGBA8;
		RHI::TextureFormat NormalFormat = RHI::TextureFormat::RGBA16F;
		RHI::TextureFormat EmissiveFormat = RHI::TextureFormat::RGBA8;
		RHI::TextureFormat DepthFormat = RHI::TextureFormat::DEPTH24STENCIL8;

		std::string_view DebugName = "GBuffer";
	};
}