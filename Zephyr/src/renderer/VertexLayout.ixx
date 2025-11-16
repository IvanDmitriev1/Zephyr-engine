export module zephyr.renderer.VertexLayout;

import std.compat;

export namespace zephyr
{
    enum class ShaderDataType : uint8_t
    {
        None = 0,
        Float, Float2, Float3, Float4,
        Int, Int2, Int3, Int4,
        Mat3, Mat4,
        Bool
    };

    struct VertexAttribute
    {
        std::string Name;
        ShaderDataType Type = ShaderDataType::None;
        uint32_t Offset = 0;
        bool Normalized = false;
    };

    constexpr uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:  return 4;
        case ShaderDataType::Float2: return 4 * 2;
        case ShaderDataType::Float3: return 4 * 3;
        case ShaderDataType::Float4: return 4 * 4;
        case ShaderDataType::Int:    return 4;
        case ShaderDataType::Int2:   return 4 * 2;
        case ShaderDataType::Int3:   return 4 * 3;
        case ShaderDataType::Int4:   return 4 * 4;
        case ShaderDataType::Mat3:   return 4 * 3 * 3;
        case ShaderDataType::Mat4:   return 4 * 4 * 4;
        case ShaderDataType::Bool:   return 1;
        default: return 0;
        }
    }

    class VertexLayout
    {
    public:
        VertexLayout() = default;
        ~VertexLayout() = default;

        VertexLayout(std::initializer_list<VertexAttribute> attributes)
            : m_Attributes(attributes)
        {
            CalculateStrideAndOffsets();
        }

        VertexLayout(const VertexLayout&) = delete;
        VertexLayout& operator=(const VertexLayout&) = delete;

        VertexLayout(VertexLayout&&) = default;
        VertexLayout& operator=(VertexLayout&&) = default;

    public:

        const std::vector<VertexAttribute>& GetAttributes() const
        {
            return m_Attributes;
        }

        uint32_t GetStride() const
        {
            return m_Stride;
        }

    private:
        void CalculateStrideAndOffsets()
        {
            uint32_t offset = 0;
            m_Stride = 0;

            for (auto& attr : m_Attributes)
            {
                attr.Offset = offset;
                const uint32_t size = ShaderDataTypeSize(attr.Type);
                offset += size;
                m_Stride += size;
            }
        }

    private:
        std::vector<VertexAttribute> m_Attributes;
        uint32_t m_Stride = 0;
    };
}