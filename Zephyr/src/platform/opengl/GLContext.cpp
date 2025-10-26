module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/Macros.h"

module zephyr.opengl.GLContext;

import zephyr.opengl.GLRendererAPI;
import zephyr.opengl.GlUtils;

namespace zephyr
{
	GLContext::GLContext(GLFWwindow* window)
		:m_window(window)
	{
	}

	Scope<IRendererAPI> GLContext::CreateRendererAPI(int width, int height)
	{
		return CreateScope<GLRendererAPI>(width, height);
	}

	void GLContext::SetSwapInterval(int interval)
	{
		glfwSwapInterval(interval);
	}

	void GLContext::Init()
	{
		glfwMakeContextCurrent(m_window);
		int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		E_ASSERT(version, "Failed to init glad!");
		std::println("OpenGL Info: {}", version);

#ifdef _DEBUG
		InitOpenGLDebugMessageCallback();
#endif // _DEBUG

	}

	void GLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}