export module Zephyr.Renderer.Resources.TextureTypes;

export import std.compat;
export import Zephyr.Core.EnumBitmask;
export import glm;

export namespace Zephyr::RHI
{
	enum class TextureFormat : uint8_t
	{
		None = 0,

		// Color
		RGBA8,
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
		glm::ivec2 Size{};
		TextureFormat Format = TextureFormat::RGBA8;
		TextureUsage Usage = TextureUsage::ShaderRead;

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

export namespace EnumBitmask
{
	template <>
	inline constexpr bool IsEnabled<Zephyr::RHI::TextureUsage> = true;
}