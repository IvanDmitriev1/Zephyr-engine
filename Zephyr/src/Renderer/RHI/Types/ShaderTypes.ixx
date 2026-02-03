export module Zephyr.Renderer.RHI.Types.ShaderTypes;

export import std.compat;

export namespace Zephyr::RHI
{
    enum class ShaderStage : uint8_t
    {
        Vertex,
        Fragment,
        Geometry,
        TessControl,
        TessEvaluation,
        Compute
    };

    struct ShaderStageDesc
    {
        ShaderStage Stage{};
        std::span<const std::byte> Code{};
    };

    struct ShaderCreateInfo
    {
        std::string_view Name{};
        std::span<const ShaderStageDesc> Stages{};
    };

	namespace UniformBindings
	{
		constexpr uint32_t Camera = 0;      // Binding 0: camera data
		constexpr uint32_t PerObject = 1;   // Binding 1: per-draw data (transform)
		constexpr uint32_t Material = 2;    // Binding 2: material properties
	}
}