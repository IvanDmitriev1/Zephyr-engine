export module Zephyr.Renderer.Types.MaterialTypes;

import Zephyr.Renderer.RHI.Types.RenderEncoderTypes;
import Zephyr.Renderer.RHI.Types.PipelineTypes;
import Zephyr.Renderer.Types.DrawCategory;

export namespace Zephyr
{
	enum class AlphaMode: uint8_t
	{
		Opaque,
		Masked,
		Blend
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
		case AlphaMode::Masked: return DrawCategory::AlphaMasked;
		case AlphaMode::Blend: return DrawCategory::Transparent;
		default: Unreachable();
		}
	}
}
