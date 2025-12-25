export module Zephyr.Renderer.Resources.ShaderTypes;

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
        std::string_view EntryPoint{ "main" };
        std::span<const std::byte> Code{};
    };

    struct ShaderCreateInfo
    {
        std::string_view Name{};
        std::span<const ShaderStageDesc> Stages{};
    };
}