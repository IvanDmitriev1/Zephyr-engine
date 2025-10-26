module;

#include <GLFW/glfw3.h>
#include "core/Macros.h"

module zephyr.opengl.GLWindow;

import zephyr.opengl.GLRendererAPI;
import zephyr.opengl.GLContext;

namespace zephyr
{
	GLWindow::GLWindow(const WindowSpecification& spec)
		:m_windowSpec(spec)
	{
		E_ASSERT(glfwInit(), "Failed to init glfw!");

#ifdef _DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif // _DEBUG

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow((int)m_windowSpec.Width, (int)m_windowSpec.Height, m_windowSpec.Title.c_str(), nullptr, nullptr);
		E_ASSERT(m_window, "Failed to create GLFW window!");

		m_context = CreateScope<GLContext>(m_window);
		m_context->Init();
		m_context->SetSwapInterval(m_windowSpec.VSync ? 1 : 0);

		m_rendererAPI = CreateScope<GLRendererAPI>((int)m_windowSpec.Width, (int)m_windowSpec.Height);

		glfwSetWindowUserPointer(m_window, this);
		glfwSetWindowSizeCallback(m_window, WindowSizeCallBack);
		glfwSetWindowCloseCallback(m_window, WindowCloseCallBack);
	}

	GLWindow::~GLWindow()
	{
		if (m_window)
		{
			glfwDestroyWindow(m_window);
			m_window = nullptr;
		}

		glfwTerminate();
	}

	float GLWindow::GetTime() const
	{
		return (float)glfwGetTime();
	}

	void GLWindow::SetEventCallback(const EventCallbackFn& callback)
	{
		m_eventCallback = callback;
	}

	void GLWindow::Update()
	{
		glfwPollEvents();
		m_context->SwapBuffers();
	}

	bool GLWindow::ShouldClose() const
	{
		return glfwWindowShouldClose(m_window) != 0;
	}


	void GLWindow::WindowSizeCallBack(GLFWwindow* window, int width, int height)
	{
		const auto& handl = *(GLWindow*)glfwGetWindowUserPointer(window);
		WindowResizeEvent e(width, height);
		handl.m_eventCallback(e);
	}

	void GLWindow::WindowCloseCallBack(GLFWwindow* window)
	{
		const auto& handl = *(GLWindow*)glfwGetWindowUserPointer(window);
		WindowClosingEvent e{};
		handl.m_eventCallback(e);
	}

	void GLWindow::ErrorCallback(int error, const char* description)
	{
		std::cout << std::format("GLFW Error: {}: {}", error, description);
	}
}