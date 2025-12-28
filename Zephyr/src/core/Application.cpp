module zephyr.app;

import zephyr.logging.LogHelpers;
import zephyr.logging.BufferedLogSink;
import zephyr.events.ApplicationEvents;
import glm;

import <spdlog/spdlog.h>;

import Zephyr.Renderer.Zephyr_RENDERER.Window;

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
    }

    void Application::Run()
    {
        m_Running = true;
        float lastTime = m_window->GetTime();

        while (m_Running)
        {
            m_window->PollEvents();

            float currentTime = m_window->GetTime();
            float dt = glm::clamp(currentTime - lastTime, 0.001f, 0.1f);
            lastTime = currentTime;

            if (!m_Minimized)
            {
                m_LayerStack.FlushPendingOps();

                m_LayerStack.OnUpdate(dt);

                m_swapchain->BeginFrame();
                m_LayerStack.OnRender();
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

    void Application::OnEvent(IEvent& e)
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