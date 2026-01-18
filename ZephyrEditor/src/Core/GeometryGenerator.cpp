module ZephyrEditor.GeometryGenerator;

using namespace Zephyr;

namespace ZephyrEditor
{
	Ref<Mesh> GeometryGenerator::CreateCube(float size /*= 1.0f*/)
	{
		const float s = size * 0.5f;

		std::vector<Vertex3D> vertices = {
			// Front face
			{{-s, -s,  s}, { 0,  0,  1}, {0, 0}},
			{{ s, -s,  s}, { 0,  0,  1}, {1, 0}},
			{{ s,  s,  s}, { 0,  0,  1}, {1, 1}},
			{{-s,  s,  s}, { 0,  0,  1}, {0, 1}},

			// Back face
			{{ s, -s, -s}, { 0,  0, -1}, {0, 0}},
			{{-s, -s, -s}, { 0,  0, -1}, {1, 0}},
			{{-s,  s, -s}, { 0,  0, -1}, {1, 1}},
			{{ s,  s, -s}, { 0,  0, -1}, {0, 1}},

			// Top face
			{{-s,  s,  s}, { 0,  1,  0}, {0, 0}},
			{{ s,  s,  s}, { 0,  1,  0}, {1, 0}},
			{{ s,  s, -s}, { 0,  1,  0}, {1, 1}},
			{{-s,  s, -s}, { 0,  1,  0}, {0, 1}},

			// Bottom face
			{{-s, -s, -s}, { 0, -1,  0}, {0, 0}},
			{{ s, -s, -s}, { 0, -1,  0}, {1, 0}},
			{{ s, -s,  s}, { 0, -1,  0}, {1, 1}},
			{{-s, -s,  s}, { 0, -1,  0}, {0, 1}},

			// Right face
			{{ s, -s,  s}, { 1,  0,  0}, {0, 0}},
			{{ s, -s, -s}, { 1,  0,  0}, {1, 0}},
			{{ s,  s, -s}, { 1,  0,  0}, {1, 1}},
			{{ s,  s,  s}, { 1,  0,  0}, {0, 1}},

			// Left face
			{{-s, -s, -s}, {-1,  0,  0}, {0, 0}},
			{{-s, -s,  s}, {-1,  0,  0}, {1, 0}},
			{{-s,  s,  s}, {-1,  0,  0}, {1, 1}},
			{{-s,  s, -s}, {-1,  0,  0}, {0, 1}}
		};

		std::vector<uint32_t> indices = {
			0,  1,  2,  2,  3,  0,   // Front
			4,  5,  6,  6,  7,  4,   // Back
			8,  9, 10, 10, 11,  8,   // Top
			12, 13, 14, 14, 15, 12,  // Bottom
			16, 17, 18, 18, 19, 16,  // Right
			20, 21, 22, 22, 23, 20   // Left
		};

		return CreateMeshFromData(vertices, indices);
	}

	Ref<Mesh> GeometryGenerator::CreateMeshFromData(const std::vector<Vertex3D>& vertices, const std::vector<uint32_t>& indices)
	{
		RHI::BufferDesc vbDesc{
				.SizeBytes = static_cast<uint32_t>(vertices.size() * sizeof(Vertex3D)),
				.Usage = RHI::BufferUsage::Vertex,
				.Access = RHI::BufferAccess::Static,
				.DebugName = "GeometryVB"
		};
		auto vb = RHI::Device::CreateBuffer(vbDesc);
		vb->SetData(std::as_bytes(std::span{ vertices.data(), vertices.size() }));

		// Create index buffer
		RHI::BufferDesc ibDesc{
			.SizeBytes = static_cast<uint32_t>(indices.size() * sizeof(uint32_t)),
			.Usage = RHI::BufferUsage::Index,
			.Access = RHI::BufferAccess::Static,
			.DebugName = "GeometryIB"
		};
		auto ib = RHI::Device::CreateBuffer(ibDesc);
		ib->SetData(std::as_bytes(std::span{ indices.data(), indices.size() }));

		// Create vertex array
		RHI::VertexArrayCreateInfo vaoInfo{
			.Layout = Vertex3D::GetLayout(),
			.VertexBuffer = vb,
			.Index = RHI::IndexBinding{
				.Buffer = ib,
				.Type = RHI::IndexType::UInt32
			},
			.DebugName = "GeometryVAO"
		};
		auto vao = RHI::Device::CreateVertexArray(vaoInfo);

		// Create mesh
		return CreateRef<Mesh>(MeshCreateDesc{
			.Vao = vao,
			.VertexCount = static_cast<uint32_t>(vertices.size()),
			.IndexCount = static_cast<uint32_t>(indices.size())
							   });
	}
}