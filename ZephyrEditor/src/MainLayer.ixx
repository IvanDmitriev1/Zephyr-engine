export module ZephyrEditor.MainLayer;

export import Zephyr.Core.Layer;
export import Zephyr.Renderer.Renderer;
export import Zephyr.Renderer.Shader.ShaderLoader;

using namespace Zephyr;

struct Vertex
{
	float Pos[2];
	float Color[3];
};

export class MainLayer : public Zephyr::Layer
{
public:
	MainLayer() : Zephyr::Layer("MainLayer")
	{
		const ShaderStageLoadInfo shaderStages[] =
		{
			{.Path = "Assets/Shaders/Triangle.vert" , .Stage = RHI::ShaderStage::Vertex  },
			{.Path = "Assets/Shaders/Triangle.frag", .Stage = RHI::ShaderStage::Fragment },
		};

		m_Shader = ShaderLoader::Load("Triangle", shaderStages);

		m_DrawItem = DrawItem{
			.Mesh = CreateTriangleMesh(),
			.Material = CreateTriangleMaterial(),
		};
	}

	void OnUpdate(float ts) override
	{
		m_Rotation += ts * 90.0f;

		glm::mat4 transform = glm::rotate(
			glm::mat4(1.0f),
			glm::radians(m_Rotation),
			glm::vec3(0.0f, 0.0f, 1.0f)  // Rotate around Z-axis (2D rotation)
		);

		m_DrawItem.Transform = transform;
	}

	void OnRender() override
	{
		Renderer::Submit(m_DrawItem);
	}

private:
	std::array<Vertex, 3> CreateTriangleVertices()
	{
		return { {
				// Position (x, y)     // Color (r, g, b)
				{ { 0.0f,  0.5f},      {1.0f, 0.0f, 0.0f} },  // Top vertex - Red
				{ {-0.5f, -0.5f},      {0.0f, 1.0f, 0.0f} },  // Bottom-left - Green
				{ { 0.5f, -0.5f},      {0.0f, 0.0f, 1.0f} }   // Bottom-right - Blue
			} };
	}

	Ref<Zephyr::Mesh> CreateTriangleMesh()
	{
		auto vertices = CreateTriangleVertices();

		auto vb = RHI::Device::CreateBuffer(RHI::BufferDesc{
			.SizeBytes = static_cast<uint32_t>(sizeof(vertices)),
			.Usage = RHI::BufferUsage::Vertex,
			.Access = RHI::BufferAccess::Static,
			.DebugName = "TriangleVB"
		});
		vb->SetData(std::as_bytes(std::span{ vertices }));

		static constexpr auto layout = RHI::MakeLayoutFromMembers<Vertex>(std::array{
			RHI::VertexAttribute{.Name = "aPos",   .Type = RHI::VertexAttributeType::Float2 },
			RHI::VertexAttribute{.Name = "aColor", .Type = RHI::VertexAttributeType::Float3 },
																   });

		auto vao = RHI::Device::CreateVertexArray(RHI::VertexArrayCreateInfo{
			.Layout = layout,
			.VertexBuffer = std::move(vb),
			.DebugName = "TriangleVAO"
		});

		MeshCreateDesc meshDesc{};
		meshDesc.Vao = vao;
		meshDesc.VertexCount = 3;
		meshDesc.IndexCount = 0;

		return CreateRef<Mesh>(meshDesc);
	}

	Ref<Zephyr::Material> CreateTriangleMaterial()
	{
		MaterialDesc matDesc{};
		matDesc.Name = "TriangleMaterial";
		matDesc.Shader = m_Shader;
		matDesc.Type = AlphaMode::Opaque;
		matDesc.Queue = RenderQueue::Geometry;

		return CreateRef<Material>(matDesc);
	}

private:
	Ref<RHI::IShader> m_Shader;
	DrawItem m_DrawItem{};

	float m_Rotation = 0.0f;
};