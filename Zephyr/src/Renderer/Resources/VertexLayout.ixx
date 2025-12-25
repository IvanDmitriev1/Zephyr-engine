export module Zephyr.Renderer.Resources.VertexLayout;

export import Zephyr.Renderer.Resources.VertexLayoutTypes;

export namespace Zephyr::RHI
{
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
		std::span<const VertexAttribute> GetAttributes() const noexcept
		{
			return { m_Attributes.data(), m_Attributes.size() };
		}

		uint32_t GetStride() const noexcept
		{
			return m_Stride;
		}

	private:
		void CalculateStrideAndOffsets() noexcept
		{
			uint32_t offset = 0;
			m_Stride = 0;

			for (auto& attr : m_Attributes)
			{
				attr.Offset = offset;
				const uint32_t size = VertexAttributeTypeSize(attr.Type);
				offset += size;
				m_Stride += size;
			}
		}

	private:
		std::vector<VertexAttribute> m_Attributes;
		uint32_t m_Stride = 0;
	};
}