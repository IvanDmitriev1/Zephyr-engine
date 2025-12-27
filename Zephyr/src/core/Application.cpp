module zephyr.app;

import zephyr.logging.LogHelpers;
import zephyr.logging.BufferedLogSink;
import zephyr.events.ApplicationEvents;
import glm;

import <spdlog/spdlog.h>;

import Zephyr.Renderer.Zephyr_RENDERER.Window;

struct Vertex
{
    float Pos[2];
    float Color[3];
};

namespace Zephyr
{
    Application::Application(const WindowSpecification& spec)
    {
        ConfigureLogging();

        m_window = Window::CreateMainWindow(spec);
        m_window->SetEventCallback(bind_event_fn(this, &Application::OnEvent));

        m_swapchain = RHI::Device::CreateSwapchain(*m_window, RHI::SwapchainDesc{
            .Size = m_window->GetSize(),
            .ColorFormat = RHI::TextureFormat::RGBA8,
            .DepthFormat = RHI::TextureFormat::DEPTH24STENCIL8,
            .DebugName = "MainSwapchain"
        });

        const ShaderStageLoadInfo shaderStages[] =
        {
            {.Path = "Assets/Shaders/Triangle.vert" , .Stage = RHI::ShaderStage::Vertex  },
            {.Path = "Assets/Shaders/Triangle.frag", .Stage = RHI::ShaderStage::Fragment },
        };

        m_Shader = ShaderLoader::Load("Triangle", shaderStages);
    }

    void Application::Run()
    {
        m_Running = true;

        float lastTime = m_window->GetTime();

        using namespace RHI;

        ColorAttachment ca{};
        ca.Load = LoadOp::Clear;
        ca.Clear = { 0.05f, 0.07f, 0.10f, 1.0f };
        const ColorAttachment colors[] = { ca };

        RenderPassDesc rp{};
        rp.Target = m_swapchain->GetBackBuffer();
        rp.Colors = colors;
        rp.DebugName = "MainPass";

        auto pipeline = Device::CreatePipeline(GraphicsPipelineDesc{
            .Shader = m_Shader,
            .Topology = PrimitiveTopology::Triangles,
            .Depth = {.DepthTestEnable = false, .DepthWriteEnable = false },
            .Blend = {.Enable = false },
            .ColorFormat = TextureFormat::RGBA8,
            .DebugName = "TrianglePipeline",
        });

        // Geometry
        const Vertex verts[3] = {
            {{ 0.0f,  0.6f}, {1.f, 0.f, 0.f}},
            {{-0.6f, -0.6f}, {0.f, 1.f, 0.f}},
            {{ 0.6f, -0.6f}, {0.f, 0.f, 1.f}},
        };

        auto vb = Device::CreateVertexBuffer(RHI::BufferDesc{
            .SizeBytes = static_cast<uint32_t>(sizeof(verts)),
            .Usage = RHI::BufferUsage::Vertex,
            .Access = RHI::BufferAccess::Static,
            .DebugName = "TriangleVB"
        });

        vb->SetData(std::as_bytes(std::span{ verts }));

        RHI::VertexLayout layout
        {
            VertexAttribute{.Name = "aPos",   .Type = VertexAttributeType::Float2, .Offset = (uint32_t)offsetof(Vertex, Pos),   .Location = 0 },
            VertexAttribute{.Name = "aColor", .Type = VertexAttributeType::Float3, .Offset = (uint32_t)offsetof(Vertex, Color), .Location = 1 },
        };

        auto vao = Device::CreateVertexArray(RHI::VertexArrayCreateInfo{
            .VertexBuffer = vb,
            .Layout = std::move(layout),
            .IndexBuffer = nullptr,
            .DebugName = "TriangleVAO"
        });

        auto cmd = Device::CreateCommandList();

        while (m_Running)
        {
            m_window->PollEvents();

            float currentTime = m_window->GetTime();
            float dt = glm::clamp(currentTime - lastTime, 0.001f, 0.1f);
            lastTime = currentTime;

            if (!m_Minimized)
            {
                cmd->BeginRenderPass(rp);

                cmd->BindPipeline(pipeline);
                cmd->BindVertexArray(vao);
                cmd->Draw(3);
                cmd->EndRenderPass();

                m_swapchain->Present();
            }
        }
    }

    LayerStack& Application::GetLayerStack()
    {
		return m_LayerStack;
    }

    LogBuffer& Application::GetLogBuffer()
    {
        return *m_LogBuffer;
    }

    void Application::ConfigureLogging()
    {
        m_LogBuffer = CreateRef<LogBuffer>();

        LoggerBuilder engineLoggerBuilder;
        engineLoggerBuilder
            .SetName("Zephyr")
            .SetLevel(LogLevel::Info)
            .SetPattern("%^[%T] [ZEPHYR] %v%$")
            .AddSink(CreateRef<BufferedLogSink>(m_LogBuffer));

        LoggerBuilder appLoggerBuilder;
        appLoggerBuilder
            .SetName("App")
            .SetLevel(LogLevel::Info)
            .SetPattern(std::format("%^[%T] [{}] %v%$", "change later"))
            .AddSink(CreateRef<BufferedLogSink>(m_LogBuffer));

        ConfigureAppLogger(appLoggerBuilder);
        ConfigureEngineLogger(engineLoggerBuilder);

        Log::Initialize(engineLoggerBuilder.Build(), appLoggerBuilder.Build());
    }

    void Application::OnEvent(const IEvent& e)
    {
        if (e.IsInCategory(EventCategoryApplication) )
        {
            const auto& appEvent = (ApplicationEvent&)e;

            if (appEvent.GetWidth() == 0 || appEvent.GetHeight() == 0)
            {
                m_Minimized = true;
            }
            else
            {
				m_Minimized = false;
            }

            if (appEvent.GetEventType() == EventType::WINDOW_CLOSING_EVENT)
            {
                m_Running = false;
            }

            if (appEvent.GetEventType() == EventType::WINDOW_RESIZE_EVENT)
            {
                m_swapchain->Resize(glm::ivec2(appEvent.GetWidth(), appEvent.GetHeight()));
            }
        }

        //m_window->UiContext().OnEvent(e);
		m_LayerStack.OnEvent(e);
    }
}