export module Zephyr.Renderer.Types.MaterialTypes;

export import Zephyr.Renderer.RHI.RenderPassEncoderTypes;
export import Zephyr.Renderer.RHI.PipelineTypes;
export import Zephyr.Renderer.Types.DrawCategory;

export namespace Zephyr
{
	enum class AlphaMode: uint8_t
	{
		Opaque,
		Transparent,
		Cutout
	};

	struct MaterialProperties
	{
		glm::vec4 AlbedoColor{ 1.0f, 1.0f, 1.0f, 1.0f };
		float Metallic = 0.0f;
		float Roughness = 0.5f;
		float AO = 1.0f;
		float NormalScale = 1.0f;
	};

	struct MaterialDesc
	{
		std::string Name{};
		Ref<RHI::IShader> Shader{};
		AlphaMode Type = AlphaMode::Opaque;

		DrawCategory Category = DrawCategory::Opaque;
		MaterialProperties Properties{};
		std::vector<RHI::ResourceBinding> Bindings{};
	};

	constexpr DrawCategory GetDefaultDrawCategory(AlphaMode mode) noexcept
	{
		switch (mode)
		{
		case AlphaMode::Opaque: return DrawCategory::Opaque;
		case AlphaMode::Cutout: return DrawCategory::AlphaMasked;
		case AlphaMode::Transparent: return DrawCategory::Transparent;
		default:
			std::unreachable();
		}
	}
}