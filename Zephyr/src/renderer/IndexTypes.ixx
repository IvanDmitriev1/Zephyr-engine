export module zephyr.renderer.IndexTypes;

import std.compat;

export namespace zephyr
{
    enum class IndexType : uint8_t
    {
        None = 0,
        UInt16,
        UInt32
    };

    constexpr uint32_t IndexTypeSize(IndexType type)
    {
        switch (type)
        {
        case IndexType::UInt16: return 2;
        case IndexType::UInt32: return 4;
        default: return 0;
        }
    }
}