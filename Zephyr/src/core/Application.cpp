module Zephyr.App;

import zephyr.logging.LogHelpers;
import zephyr.logging.BufferedLogSink;
import zephyr.events.ApplicationEvents;

import <spdlog/spdlog.h>;

import Zephyr.Renderer.Platform.Window;

namespace Zephyr
{
    Application::Application(const WindowSpecification& spec)
    {
        ConfigureLogging();

        m_window = Window::CreateMainWindow(spec);
        m_window->SetEventCallback(bind_event_fn(this, &Application::OnEventDispatch));
        m_uiRenderContext = m_window->CreateUiContext();

		log::Info("Current working path: {}", std::filesystem::current_path().string());
    }

    void Application::Run()
    {
		OnInit();

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
				OnUpdate(dt);
				OnRender();

                m_uiRenderContext->BeginFrame();
				OnUiRender();
                m_uiRenderContext->EndFrame();

				m_window->SwapBuffers();
            }
        }
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


        Log::Initialize(engineLoggerBuilder.Build(), appLoggerBuilder.Build());
    }

    void Application::OnEventDispatch(IEvent& e)
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

		OnEvent(e);
    }
}
