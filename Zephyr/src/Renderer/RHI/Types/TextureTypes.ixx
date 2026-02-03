export module Zephyr.Renderer.RHI.Types.TextureTypes;

export import Zephyr.Core.EnumBitmask;
export import Zephyr.Renderer.Types.CommonTypes;
export import std.compat;

export namespace Zephyr::RHI
{
	using TextureHandle = uint32_t;

	enum class TextureFormat : uint8_t
	{
		Invalid = 0,

		// Color
		RGBA8,
		RGBA16F,
		RED_INTEGER,
		//B8G8R8A8,

		// Depth/stencil
		DEPTH24STENCIL8,
	};

	enum class TextureFilter : uint8_t
	{
		Nearest,
		Linear,
		NearestMipmapNearest,
		LinearMipmapLinear
	};

	enum class TextureWrap : uint8_t
	{
		Repeat,
		ClampToEdge,
		ClampToBorder,
		MirroredRepeat
	};

	enum class TextureUsage : uint32_t
	{
		None = 0,
		ShaderRead = 1 << 0,
		RenderTarget = 1 << 1,
		TransferSrc = 1 << 2,
		TransferDst = 1 << 3
	};

	struct TextureDesc
	{
		Extent2D Size{};
		TextureFormat Format = TextureFormat::RGBA8;
		TextureUsage Usage = TextureUsage::ShaderRead;

		uint32_t MipLevels = 1;      // 0 = auto-generate max mips
		uint32_t ArrayLayers = 1;    // For texture arrays
		uint32_t SampleCount = 1;    // For MSAA

		std::string_view DebugName{};
	};

	struct SamplerSpecification
	{
		TextureFilter MinFilter = TextureFilter::Linear;
		TextureFilter MagFilter = TextureFilter::Linear;
		TextureWrap WrapU = TextureWrap::Repeat;
		TextureWrap WrapV = TextureWrap::Repeat;
		TextureWrap WrapW = TextureWrap::Repeat;
		float MaxAnisotropy = 1.0f;
	};


	constexpr bool IsDepth(TextureFormat fmt)
	{
		return fmt == TextureFormat::DEPTH24STENCIL8;
	}
}
