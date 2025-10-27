module;

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "core/Macros.h"

module zephyr.app;

import zephyr.opengl.GLWindow;
import glm;

namespace zephyr
{
    Application::Application(const WindowSpecification& spec)
        : m_windowSpec{ spec }
    {
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

            m_LayerStack.OnUpdate(dt);

            renderer.StartOfTheFrame();
            m_LayerStack.OnRender();
            renderer.EndOfTheFrame();

            uiRenderContext.BeginFrame();
            m_LayerStack.OnUiRender();
            uiRenderContext.EndFrame();

            m_window->Update();
		}
    }

    void Application::OnEvent(const IEvent& e)
    {
        if (e.IsInCategory(EventCategoryApplication) )
        {
            const auto& appEvent = (ApplicationEvent&)e;

            if (appEvent.GetWidth() == 0 || appEvent.GetHeight() == 0)
            {
                //_minimized = true;
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