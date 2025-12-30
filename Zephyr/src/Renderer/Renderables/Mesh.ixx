export module Zephyr.Renderer.Renderables.Mesh;

export import Zephyr.Renderer.Core.IVertexArray;

export namespace Zephyr
{
	class Mesh
	{
	public:
		Mesh(Ref<RHI::IVertexArray> vao)
			:m_VertexArray(std::move(vao)) {}

		void SetVertexCount(uint32_t count) { m_VertexCount = count; }

		Ref<RHI::IVertexArray> GetVertexArray() const { return m_VertexArray; }
		uint32_t GetVertexCount() const { return m_VertexCount; }
		uint32_t GetIndexCount() const { return m_IndexCount; }

	private:
		Ref<RHI::IVertexArray> m_VertexArray;
		uint32_t m_VertexCount = 0;
		uint32_t m_IndexCount = 0;
	};
}