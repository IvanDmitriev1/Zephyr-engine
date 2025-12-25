module Zephyr.Renderer.OpenGL.Window;

import Zephyr.Core.CoreTypes;
import zephyr.events.ApplicationEvents;

namespace Zephyr::OpenGL
{
	void GlWindow::ErrorCallback(int error, const char* description)
	{
		log::Critical("GLFW Error: {}: {}", error, description);
	}

	void GlWindow::WindowCloseCallBack(GLFWwindow* window)
	{
		auto* self = reinterpret_cast<GlWindow*>(glfwGetWindowUserPointer(window));

		WindowClosingEvent e{};
		self->m_eventCallback(e);
	}

	void GlWindow::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		auto* self = reinterpret_cast<GlWindow*>(glfwGetWindowUserPointer(window));

		self->m_size.x = width;
		self->m_size.y = height;

		WindowResizeEvent e(width, height);
		self->m_eventCallback(e);
	}
}