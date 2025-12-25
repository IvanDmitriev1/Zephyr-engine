export module Zephyr.Renderer.Resources.BufferTypes;

export import std.compat;

export namespace Zephyr::RHI
{
    enum class BufferUsage : uint32_t
    {
        Vertex = 1 << 0,
        Index = 1 << 1,
        Uniform = 1 << 2,
        Storage = 1 << 3,
        TransferSrc = 1 << 4,
        TransferDst = 1 << 5,
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
    };
}