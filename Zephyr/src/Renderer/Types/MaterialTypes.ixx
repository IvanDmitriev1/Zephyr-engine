export module Zephyr.Renderer.Types.MaterialTypes;

export import Zephyr.Renderer.RHI.RenderPassEncoderTypes;
export import Zephyr.Renderer.RHI.PipelineTypes;
export import Zephyr.Renderer.Types.RenderPhase;

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

		RenderPhase Phase = RenderPhase::Geometry;
		MaterialProperties Properties{};
		std::vector<RHI::ResourceBinding> Bindings{};
	};

	constexpr RenderPhase GetDefaultPhase(AlphaMode mode) noexcept
	{
		switch (mode)
		{
		case AlphaMode::Opaque: return RenderPhase::Geometry;
		case AlphaMode::Cutout: return RenderPhase::AlphaTest;
		case AlphaMode::Transparent: return RenderPhase::Transparent;
		default: return RenderPhase::Geometry;
		}
	}
}