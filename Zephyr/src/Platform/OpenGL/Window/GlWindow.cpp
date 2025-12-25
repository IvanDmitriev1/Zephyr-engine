module;

#include <GLFW/glfw3.h>
#include <glad/glad.h>

module Zephyr.Renderer.OpenGL.Window;

import Zephyr.Core.CoreTypes;
import Zephyr.Renderer.OpenGL.Debug;

namespace Zephyr::Window
{
	IWindow* g_Window = nullptr;

	Scope<IWindow> CreateMainWindow(const WindowSpecification& spec)
	{
		auto window = CreateScope<OpenGL::GlWindow>(spec);
		g_Window = window.get();

		return window;
	}

	IWindow& GetMainWindow()
	{
		if (!g_Window)
			throw std::runtime_error("Window::GetMainWindow() called before Window::CreateMainWindow().");

		return *g_Window;
	}
}

namespace Zephyr::OpenGL
{
	GlWindow::GlWindow(const WindowSpecification& spec)
		:m_size(spec.Width, spec.Height),
		m_vsync(spec.VSync)
	{
		Assert(glfwInit(), "Failed to init glfw!");

#ifdef _DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif // _DEBUG

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(m_size.x, m_size.y, spec.Title.data(), nullptr, nullptr);
		Assert(m_window, "Failed to create GLFW window!");

		glfwMakeContextCurrent(m_window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			Assert(false, "Failed to init glad!");

#ifdef _DEBUG
		RHI::OpenGL::Debug::InitOpenGLDebugMessageCallback();
#endif // _DEBUG

		GLint major = 0, minor = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		log::Info("OpenGL version: {}.{}", major, minor);

		glfwSetWindowUserPointer(m_window, this);
		glfwSetWindowCloseCallback(m_window, WindowCloseCallBack);
		glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);

		glfwSwapInterval(m_vsync ? 1 : 0);
	}

	GlWindow::~GlWindow()
	{
		if (m_window)
		{
			glfwDestroyWindow(m_window);
			m_window = nullptr;
		}
		
		glfwTerminate();
	}

	float GlWindow::GetTime() const noexcept
	{
		return static_cast<float>(glfwGetTime());
	}

	void GlWindow::SetEventCallback(const EventCallbackFn& callback)
	{
		m_eventCallback = callback;
	}

	void GlWindow::PollEvents()
	{
		glfwPollEvents();
	}

	bool GlWindow::ShouldClose() const
	{
		return glfwWindowShouldClose(m_window) != 0;
	}
	void GlWindow::SwapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}
