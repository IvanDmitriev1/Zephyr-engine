module;

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "core/Macros.h"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

module zephyr.app;

import zephyr.logging.LogHelpers;
import zephyr.opengl.GLWindow;
import glm;

namespace zephyr
{
    Application::Application(const WindowSpecification& spec)
        : m_windowSpec{ spec }
    {
        ConfigureLogging();

        m_window = CreateScope<GLWindow>(spec);
        m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    }

    void Application::Run()
    {
        m_Running = true;
        IRendererAPI& renderer = m_window->Gfx();
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

                renderer.StartOfTheFrame();
                m_LayerStack.OnRender();
                renderer.EndOfTheFrame();

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

    BufferedLogSink<>& Application::GetLogSink()
    {
        return *m_BufferedLogSink;
    }

    void Application::ConfigureLogging()
    {
        m_BufferedLogSink = CreateRef<BufferedLogSink<>>();

        LoggerBuilder engineLoggerBuilder;
        engineLoggerBuilder
            .SetName("Zephyr")
            .SetLevel(LogLevel::Info)
            .SetPattern("%^[%T] [ZEPHYR] %v%$")
            .AddSink(m_BufferedLogSink);

        LoggerBuilder appLoggerBuilder;
        appLoggerBuilder
            .SetName("App")
            .SetLevel(LogLevel::Info)
            .SetPattern("%^[%T] [APP] %v%$")
            .AddSink(m_BufferedLogSink);

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

            m_window->Gfx().OnEvent(appEvent);
        }

        m_window->UiContext().OnEvent(e);
		m_LayerStack.OnEvent(e);
    }
}