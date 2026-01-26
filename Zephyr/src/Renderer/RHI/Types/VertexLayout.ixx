export module Zephyr.Renderer.RHI.VertexLayout;

export import Zephyr.Renderer.RHI.VertexLayoutTypes;

export namespace Zephyr::RHI
{
	class VertexLayout
    {
	public:
		constexpr VertexLayout() noexcept = default;

		template <size_t N>
			requires (N <= 16)
		constexpr VertexLayout(std::array<VertexAttribute, N>&& attributes, uint32_t stride) noexcept
			: m_Size(static_cast<uint32_t>(N)), m_Stride(stride)
		{
			for (size_t i = 0; i < N; ++i)
			{
				m_Attributes[i] = std::move(attributes[i]);
			}
		}

		std::span<const VertexAttribute> GetAttributes() const noexcept
		{
			return { m_Attributes.data(), m_Size };
		}

		uint32_t GetStride() const noexcept
		{
			return m_Stride;
		}

	private:
		std::array<VertexAttribute, 16> m_Attributes{};
		uint32_t m_Size;
		uint32_t m_Stride = 0;
    };

	template<typename Vertex>
	concept TriviallyCopyableVertex = std::is_trivially_copyable_v<Vertex>;


	template <typename Vertex, size_t N>
		requires TriviallyCopyableVertex<Vertex> && (N <= 16)
	[[nodiscard]] consteval inline VertexLayout MakeLayoutFromMembers(std::array<VertexAttribute, N>&& attributes)
	{
		uint32_t offset = 0;
		uint32_t location = 0;

		for (auto& attr : attributes)
		{
			attr.Offset = offset;
			attr.Location = location;

			offset += VertexAttributeTypeSize(attr.Type);
			location += VertexAttributeTypeIsMatrix(attr.Type)
				? VertexAttributeMatrixColumns(attr.Type)
				: 1u;
		}

		//Assert(offset == sizeof(Vertex), "MakeLayoutFromMembers: calculation error in vertex layout");

		return VertexLayout(std::move(attributes), offset);
	}
}