module;

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "core/Macros.h"

module zephyr.app;

import zephyr.opengl.GLWindow;

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

        while (m_Running)
        {
            glClearColor(0.10f, 0.10f, 0.12f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            m_window->Update();
		}
    }

    void Application::OnEvent(const IEvent& e)
    {
        if (e.GetCategoryFlags() == EventCategoryApplication)
        {
            const auto& appEvent = (ApplicationEvent&)e;

            if (appEvent.GetWidth() == 0 || appEvent.GetHeight() == 0)
            {
                //_minimized = true;
            }

            if (appEvent.GetEventType() == EventType::WINDOW_CLOSING_EVENT)
            {
                //_windowRunning = false;
            }

            m_window->Gfx().OnEvent(appEvent);
        }

    }
}