export module Zephyr.Renderer.Resources.VertexLayoutTypes;

export import std.compat;
export import Zephyr.Core.CoreTypes;

export namespace Zephyr::RHI
{
    enum class VertexAttributeType : uint8_t
    {
        None = 0,
        Float, Float2, Float3, Float4,
        Int, Int2, Int3, Int4,
        Mat3, Mat4,
        Bool
    };

    struct VertexAttribute
    {
        std::string_view Name{};
        VertexAttributeType Type{};
        uint32_t Offset{};
        uint32_t Location = 0;
        bool Normalized = false;
    };


    class VertexLayout
    {
    public:
        VertexLayout() = default;

        template<size_t N>
        VertexLayout(std::array<VertexAttribute, N>&& attributes, uint32_t stride)
            :m_Attributes(attributes.begin(), attributes.end()),
            m_Stride(stride) 
        {
            Assert(m_Stride, "VertexLayout: stride must be > 0");
        }

        ~VertexLayout() = default;

        VertexLayout(const VertexLayout&) = delete;
        VertexLayout& operator=(const VertexLayout&) = delete;

        VertexLayout(VertexLayout&& other)
            : m_Attributes(std::move(other.m_Attributes)),
            m_Stride(other.m_Stride)
        {
            other.m_Stride = 0;
        }

        VertexLayout& operator=(VertexLayout&& other)
        {
            if (this == &other)
                return *this;

            m_Attributes = std::move(other.m_Attributes);
            m_Stride = other.m_Stride;

            other.m_Stride = 0;
            return *this;
        }

    public:
        std::span<const VertexAttribute> GetAttributes() const noexcept
        {
            return { m_Attributes.data(), m_Attributes.size() };
        }

        uint32_t GetStride() const noexcept
        {
            return m_Stride;
        }

    private:
        std::vector<VertexAttribute> m_Attributes{};
        uint32_t m_Stride = 0;
    };


    constexpr uint32_t VertexAttributeTypeSize(VertexAttributeType type)
    {
        switch (type)
        {
        case VertexAttributeType::Float:  return 4;
        case VertexAttributeType::Float2: return 4 * 2;
        case VertexAttributeType::Float3: return 4 * 3;
        case VertexAttributeType::Float4: return 4 * 4;
        case VertexAttributeType::Int:    return 4;
        case VertexAttributeType::Int2:   return 4 * 2;
        case VertexAttributeType::Int3:   return 4 * 3;
        case VertexAttributeType::Int4:   return 4 * 4;
        case VertexAttributeType::Mat3:   return 4 * 3 * 3;
        case VertexAttributeType::Mat4:   return 4 * 4 * 4;
        case VertexAttributeType::Bool:   return 1;
        default: return 0;
        }
    }

    constexpr bool VertexAttributeTypeIsInteger(VertexAttributeType t) noexcept
    {
        return t == VertexAttributeType::Int || t == VertexAttributeType::Int2 ||
            t == VertexAttributeType::Int3 || t == VertexAttributeType::Int4 ||
            t == VertexAttributeType::Bool;
    }

    constexpr bool VertexAttributeTypeIsMatrix(VertexAttributeType t) noexcept
    {
        return t == VertexAttributeType::Mat3 || t == VertexAttributeType::Mat4;
    }

    constexpr uint32_t VertexAttributeTypeComponentCount(VertexAttributeType t) noexcept
    {
        switch (t)
        {
        case VertexAttributeType::Float:  return 1;
        case VertexAttributeType::Float2: return 2;
        case VertexAttributeType::Float3: return 3;
        case VertexAttributeType::Float4: return 4;
        case VertexAttributeType::Int:    return 1;
        case VertexAttributeType::Int2:   return 2;
        case VertexAttributeType::Int3:   return 3;
        case VertexAttributeType::Int4:   return 4;
        case VertexAttributeType::Bool:   return 1;
            // Mat handled separately (split into columns)
        default: return 0;
        }
    }

    constexpr uint32_t VertexAttributeMatrixColumns(VertexAttributeType type) noexcept
    {
        switch (type)
        {
        case VertexAttributeType::Mat3: return 3;
        case VertexAttributeType::Mat4: return 4;
        default: return 1;
        }
    }
}