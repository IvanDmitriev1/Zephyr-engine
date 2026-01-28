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

	Ref<Mesh> GeometryGenerator::CreateSphere(
		float radius /*= 0.5f*/,
		uint32_t stacks /*= 16*/,
		uint32_t slices /*= 32*/)
	{
		// Minimums for a valid sphere
		stacks = std::max(stacks, 2u);
		slices = std::max(slices, 3u);

		const float pi = glm::pi<float>();
		const float twoPi = glm::two_pi<float>();

		std::vector<Vertex3D> vertices;
		std::vector<uint32_t> indices;

		// Vertex count: top + rings + bottom
		const uint32_t ringCount = stacks - 1;                 // excludes poles
		const uint32_t ringVerts = slices + 1;                 // seam duplicate
		const uint32_t vertexCount = 2u + ringCount * ringVerts;

		vertices.reserve(vertexCount);

		// --- Top pole ---
		{
			const glm::vec3 pos{ 0.0f, radius, 0.0f };
			const glm::vec3 nrm{ 0.0f, 1.0f, 0.0f };
			const glm::vec2 uv{ 0.0f, 0.0f };                  // arbitrary at pole
			vertices.push_back(Vertex3D{ pos, nrm, uv });
		}

		// --- Rings (theta from 0..pi, excluding poles) ---
		for (uint32_t i = 1; i <= stacks - 1; ++i)
		{
			const float v = static_cast<float>(i) / static_cast<float>(stacks); // (0,1)
			const float theta = v * pi;                                         // (0,pi)

			const float sinT = std::sin(theta);
			const float cosT = std::cos(theta);

			for (uint32_t j = 0; j <= slices; ++j)
			{
				const float u = static_cast<float>(j) / static_cast<float>(slices); // [0,1]
				const float phi = u * twoPi;                                         // [0,2pi]

				const float sinP = std::sin(phi);
				const float cosP = std::cos(phi);

				const glm::vec3 unitPos{
					sinT * cosP,
					cosT,
					sinT * sinP
				};

				const glm::vec3 pos = unitPos * radius;
				const glm::vec3 nrm = unitPos;                // already unit length
				const glm::vec2 uv{ u, v };                  // v down from top

				vertices.push_back(Vertex3D{ pos, nrm, uv });
			}
		}

		// --- Bottom pole ---
		const uint32_t bottomIndex = static_cast<uint32_t>(vertices.size());
		{
			const glm::vec3 pos{ 0.0f, -radius, 0.0f };
			const glm::vec3 nrm{ 0.0f, -1.0f, 0.0f };
			const glm::vec2 uv{ 0.0f, 1.0f };                  // arbitrary at pole
			vertices.push_back(Vertex3D{ pos, nrm, uv });
		}

		// --- Indices ---
		// Top cap: triangles fan from top pole to first ring
		const uint32_t topIndex = 0;
		const uint32_t firstRingStart = 1;

		indices.reserve(
			(slices * 3u) +                       // top cap
			((ringCount > 1 ? (ringCount - 1) : 0) * slices * 6u) + // middle
			(slices * 3u)                         // bottom cap
		);

		// Top cap
		for (uint32_t j = 0; j < slices; ++j)
		{
			const uint32_t a = firstRingStart + j;
			const uint32_t b = firstRingStart + j + 1;

			// Winding chosen for outward-facing triangles (CCW front face in OpenGL).
			indices.push_back(topIndex);
			indices.push_back(b);
			indices.push_back(a);
		}

		// Middle quads between rings (if we have 2+ rings)
		for (uint32_t ring = 0; ring + 1 < ringCount; ++ring)
		{
			const uint32_t curr = firstRingStart + ring * ringVerts;
			const uint32_t next = curr + ringVerts;

			for (uint32_t j = 0; j < slices; ++j)
			{
				const uint32_t a = curr + j;
				const uint32_t d = curr + j + 1;
				const uint32_t b = next + j;
				const uint32_t c = next + j + 1;

				// Two triangles per quad
				indices.push_back(a);
				indices.push_back(b);
				indices.push_back(d);

				indices.push_back(d);
				indices.push_back(b);
				indices.push_back(c);
			}
		}

		// Bottom cap: triangles fan to bottom pole from last ring
		const uint32_t lastRingStart = firstRingStart + (ringCount - 1) * ringVerts;

		for (uint32_t j = 0; j < slices; ++j)
		{
			const uint32_t a = lastRingStart + j;
			const uint32_t b = lastRingStart + j + 1;

			indices.push_back(bottomIndex);
			indices.push_back(a);
			indices.push_back(b);
		}

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
			.IndexCount = static_cast<uint32_t>(indices.size()),
			.LocalBounds = AABB::ComputeLocalBounds({vertices.data(), vertices.size()})
							   });
	}
}