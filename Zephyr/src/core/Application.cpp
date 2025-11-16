module;

#include <GLFW/glfw3.h>
#include <glad/glad.h>

module zephyr.app;

import zephyr.logging.LogHelpers;
import zephyr.logging.BufferedLogSink;
import zephyr.opengl.GLWindow;
import zephyr.renderer.Renderer;
import glm;

import <spdlog/spdlog.h>;

namespace zephyr
{
    Application::Application(const WindowSpecification& spec)
        : m_windowSpec{ spec }
    {
        ConfigureLogging();

        m_window = CreateScope<GLWindow>(spec);
        m_window->SetEventCallback(bind_event_fn(this, &Application::OnEvent));
    }

    void Application::Run()
    {
        m_Running = true;
		IUiRenderContext& uiRenderContext = m_window->UiContext();

        float lastTime = m_window->GetTime();

        while (m_Running)
        {
            float currentTime = m_window->GetTime();
            float dt = glm::clamp(currentTime - lastTime, 0.001f, 0.1f);
            lastTime = currentTime;

            if (!m_Minimized)
            {
                m_LayerStack.OnUpdate(dt);

                // 3D: some layer should set camera each frame:
                // Renderer::SetViewProjection(camera.GetViewProjection());
                // For now, identity:
                Renderer::SetViewProjection(glm::mat4(1.0f));

                Renderer::BeginFrame();
                m_LayerStack.OnRender();
                Renderer::EndFrame();

                uiRenderContext.BeginFrame();
                m_LayerStack.OnUiRender();
                uiRenderContext.EndFrame();
            }

            m_window->Update();
		}
    }

    LayerStack& Application::GetLayerStack()
    {
		return m_LayerStack;
    }

    IWindow& Application::GetWindow()
    {
		return *m_window;
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
            .SetPattern(std::format("%^[%T] [{}] %v%$", m_windowSpec.Title))
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
        }

        m_window->UiContext().OnEvent(e);
		m_LayerStack.OnEvent(e);
    }
}