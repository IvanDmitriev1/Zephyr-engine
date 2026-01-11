export module Zephyr.Renderer.Resources.MaterialTypes;

export import Zephyr.Renderer.Resources.RenderPassEncoderTypes;
export import Zephyr.Renderer.Resources.PipelineTypes;
export import Zephyr.Renderer.Resources.RenderQueueTypes;

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

		RenderQueue Queue = RenderQueue::Geometry;
		MaterialProperties Properties{};
		std::vector<RHI::ResourceBinding> Bindings{};
	};

	constexpr RenderQueue GetDefaultQueue(AlphaMode mode) noexcept
	{
		switch (mode)
		{
		case AlphaMode::Opaque: return RenderQueue::Geometry;
		case AlphaMode::Cutout: return RenderQueue::AlphaTest;
		case AlphaMode::Transparent: return RenderQueue::Transparent;
		default: return RenderQueue::Geometry;
		}
	}
}