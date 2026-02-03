export module Zephyr.Renderer.RHI.Types.BufferTypes;

export import Zephyr.Core.EnumBitmask;
export import std.compat;

export namespace Zephyr::RHI
{
    enum class BufferUsage : uint32_t
    {
		None = 0,
        Vertex = 1 << 0,
        Index = 1 << 1,
        Uniform = 1 << 2,
        Storage = 1 << 3,
		Indirect = 1u << 4,
		CopySrc = 1u << 5,
		CopyDst = 1u << 6,
    };

    enum class BufferAccess : uint8_t
    {
        Static,   // GPU read-only (upload once)
        Dynamic,  // CPU updates frequently
        Streaming // CPU writes every frame
    };

    struct BufferDesc
    {
        uint32_t SizeBytes = 0;
        BufferUsage Usage = BufferUsage::Vertex;
        BufferAccess Access = BufferAccess::Static;

        std::string_view DebugName{};
    };
}