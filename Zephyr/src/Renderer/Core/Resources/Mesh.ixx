export module Zephyr.Renderer.Resources.Mesh;

export import Zephyr.Renderer.RHI.Interfaces.IVertexArray;
export import Zephyr.Renderer.Types.Frustum;

export namespace Zephyr
{
	struct MeshCreateDesc
	{
		Ref<RHI::IVertexArray> Vao;
		uint32_t VertexCount{};
		uint32_t IndexCount{};
		AABB LocalBounds{};
	};

	class Mesh
	{
	public:
		Mesh(MeshCreateDesc desc)
			:m_VertexArray(std::move(desc.Vao)),
			m_VertexCount(desc.VertexCount),
			m_IndexCount(desc.IndexCount),
			m_LocalBounds(desc.LocalBounds)
		{}

		Ref<RHI::IVertexArray> GetVertexArray() const { return m_VertexArray; }
		uint32_t GetVertexCount() const { return m_VertexCount; }
		uint32_t GetIndexCount() const { return m_IndexCount; }
		AABB GetBounds() const noexcept { return m_LocalBounds; }

	private:
		Ref<RHI::IVertexArray> m_VertexArray;
		uint32_t m_VertexCount = 0;
		uint32_t m_IndexCount = 0;
		AABB m_LocalBounds{};
	};
}