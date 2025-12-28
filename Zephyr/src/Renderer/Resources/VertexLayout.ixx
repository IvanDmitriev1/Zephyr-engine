export module Zephyr.Renderer.Resources.VertexLayout;

export import Zephyr.Renderer.Resources.VertexLayoutTypes;

export namespace Zephyr::RHI
{
    template<typename Vertex, size_t N>
        requires std::is_trivially_copyable_v<Vertex>
    [[nodiscard]] constexpr inline VertexLayout MakeLayoutFromMembers(std::array<VertexAttribute, N>&& attributes)
    {
        uint32_t offset = 0;
        uint32_t location = 0;

        for (auto& attr : attributes)
        {
            attr.Offset = offset;
            attr.Location = location;

            offset += VertexAttributeTypeSize(attr.Type);
            location += VertexAttributeTypeIsMatrix(attr.Type) ? VertexAttributeMatrixColumns(attr.Type) : 1u;
        }

        Assert(offset == sizeof(Vertex), "MakeLayoutFromMembers: calculation error in vertex layout");

        return VertexLayout(std::move(attributes), static_cast<uint32_t>(sizeof(Vertex)));
    }
}