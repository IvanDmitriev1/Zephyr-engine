export module Zephyr.Renderer.Resources.BufferTypes;

export import Zephyr.Core.EnumBitmask;
export import std.compat;

export namespace Zephyr::RHI
{
    enum class BufferUsage : uint32_t
    {
        Vertex = 1 << 0,
        Index = 1 << 1,
        Uniform = 1 << 2,
        Storage = 1 << 3,
    };

    enum class BufferAccess : uint8_t
    {
        Static,   // GPU read-only (upload once)
        Dynamic,  // CPU updates frequently
        Streaming // CPU writes every frame
    };

    enum class IndexType : uint8_t
    {
        UInt16,
        UInt32
    };

    struct BufferDesc
    {
        uint32_t SizeBytes = 0;
        BufferUsage Usage = BufferUsage::Vertex;
        BufferAccess Access = BufferAccess::Static;

        std::string_view DebugName{};
    };

    struct IndexBufferDesc : BufferDesc
    {
        IndexType Type = IndexType::UInt32;

        inline BufferDesc ToBufferDesc()
        {
            return BufferDesc{
                .SizeBytes = SizeBytes,
                .Usage = Usage,
                .Access = Access,
                .DebugName = DebugName
            };
        }
    };

    constexpr uint32_t GetIndexSize(IndexType type)
    {
        switch (type)
        {
        case IndexType::UInt16: return sizeof(uint16_t);
        case IndexType::UInt32: return sizeof(uint32_t);
        default:
            break;
        }

        throw std::runtime_error("GetIndexSize: unsupported IndexType");
    }
}

export namespace EnumBitmask
{
    template <>
    inline constexpr bool IsEnabled<Zephyr::RHI::BufferUsage> = true;
}