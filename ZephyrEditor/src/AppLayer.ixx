module;
export module ZephyrEditor.AppLayer;

export import zephyr.core.Layer;
export import Zephyr.Renderer.Shader.ShaderLoader;

using namespace Zephyr;

struct Vertex
{
	float Pos[2];
	float Color[3];
};

export class AppLayer : public Zephyr::Layer
{
public:
	AppLayer() : Layer("test1")
	{
		const ShaderStageLoadInfo shaderStages[] =
		{
			{.Path = "Assets/Shaders/Triangle.vert" , .Stage = RHI::ShaderStage::Vertex  },
			{.Path = "Assets/Shaders/Triangle.frag", .Stage = RHI::ShaderStage::Fragment },
		};

		m_Shader = ShaderLoader::Load("Triangle", shaderStages);
		m_Cmd = RHI::Device::CreateCommandList();

        m_Pipeline = RHI::Device::CreatePipeline(RHI::GraphicsPipelineDesc{
            .Shader = m_Shader,
            .Topology = RHI::PrimitiveTopology::Triangles,
            .Rasterizer = RHI::RasterizerState { .Polygon = RHI::PolygonMode::Wireframe },
            .Depth = {.DepthTestEnable = false, .DepthWriteEnable = false },
            .Blend = {.Enable = false },
            .ColorFormat = RHI::TextureFormat::RGBA8,
            .DebugName = "TrianglePipeline",
                                               });

        // Geometry
        const Vertex verts[3] = {
            {{ 0.0f,  0.6f}, {1.f, 0.f, 0.f}},
            {{-0.6f, -0.6f}, {0.f, 1.f, 0.f}},
            {{ 0.6f, -0.6f}, {0.f, 0.f, 1.f}},
        };

        const Vertex verts2[3] = {
            {{ 0.6f,  0.5f}, {1, 1, 0}},
            {{ 0.3f, -0.3f}, {0, 1, 1}},
            {{ 0.9f, -0.3f}, {1, 0, 1}},
        };

        auto vb = RHI::Device::CreateBuffer(RHI::BufferDesc{
            .SizeBytes = static_cast<uint32_t>(sizeof(verts)),
            .Usage = RHI::BufferUsage::Vertex,
            .Access = RHI::BufferAccess::Static,
            .DebugName = "TriangleVB"
                                             });

		auto vb2 = RHI::Device::CreateBuffer(RHI::BufferDesc{
			.SizeBytes = static_cast<uint32_t>(sizeof(verts2)),
			.Usage = RHI::BufferUsage::Vertex,
			.Access = RHI::BufferAccess::Static,
			.DebugName = "TriangleVB"
												  });
        
        vb->SetData(std::as_bytes(std::span{ verts }));
        vb2->SetData(std::as_bytes(std::span{ verts2 }));

        constexpr auto layout = RHI::MakeLayoutFromMembers<Vertex>(std::array{
             RHI::VertexAttribute{.Name = "aPos",   .Type = RHI::VertexAttributeType::Float2 },
             RHI::VertexAttribute{.Name = "aColor", .Type = RHI::VertexAttributeType::Float3 },
        });

        m_Vao = RHI::Device::CreateVertexArray(RHI::VertexArrayCreateInfo{
			.Layout = layout,
            .VertexBuffer = std::move(vb),
            .DebugName = "TriangleVAO"
        });

        m_Vao2 = RHI::Device::CreateVertexArray(RHI::VertexArrayCreateInfo{
					.Layout = layout,
                    .VertexBuffer = std::move(vb2),
                    .DebugName = "TriangleVAO"
        });
	}

	~AppLayer() override = default;

    void OnRender() override
    {
        RHI::ColorAttachment ca{};
        ca.Load = RHI::LoadOp::Clear;
        ca.Clear = { 0.05f, 0.07f, 0.10f, 1.0f };
        const RHI::ColorAttachment colors[] = { ca };

        RHI::RenderPassDesc rp{};
        //rp.Target = Zephyr::Renderer::GetMainFrameBuffer();
        rp.Colors = colors;
        rp.DebugName = "MainPass";

        m_Cmd->BeginRenderPass(rp);

        m_Cmd->BindPipeline(m_Pipeline);
        m_Cmd->BindVertexArray(m_Vao);
        m_Cmd->Draw(3, 0);

		m_Cmd->BindVertexArray(m_Vao2);
		m_Cmd->Draw(3, 0);

        m_Cmd->EndRenderPass();
    }

private:
	Ref<RHI::IShader> m_Shader;
	Ref<RHI::ICommandList> m_Cmd;
	Ref<RHI::IVertexArray> m_Vao;
    Ref<RHI::IVertexArray> m_Vao2;
    Ref<RHI::IPipeline> m_Pipeline;
};