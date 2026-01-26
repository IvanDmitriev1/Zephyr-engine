export module Zephyr.Renderer.Renderables.Mesh;

export import Zephyr.Renderer.RHI.IVertexArray;

export namespace Zephyr
{
	struct MeshCreateDesc
	{
		Ref<RHI::IVertexArray> Vao;
		uint32_t VertexCount{};
		uint32_t IndexCount{};
	};

	class Mesh
	{
	public:
		Mesh(MeshCreateDesc desc)
			:m_VertexArray(std::move(desc.Vao)),
			m_VertexCount(desc.VertexCount),
			m_IndexCount(desc.IndexCount)
		{}

		Ref<RHI::IVertexArray> GetVertexArray() const { return m_VertexArray; }
		uint32_t GetVertexCount() const { return m_VertexCount; }
		uint32_t GetIndexCount() const { return m_IndexCount; }

	private:
		Ref<RHI::IVertexArray> m_VertexArray;
		uint32_t m_VertexCount = 0;
		uint32_t m_IndexCount = 0;
	};
}