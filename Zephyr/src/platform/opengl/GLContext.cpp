module;

#include <glad/glad.h>

module zephyr.opengl.GLContext;

import zephyr.opengl.GLRendererAPI;
import zephyr.opengl.GlUtils;
import zephyr.opengl.ImGuiGLRenderContext;

namespace zephyr
{
	GLContext::GLContext(GLFWwindow* window)
		:m_window(window)
	{
	}

	Scope<IUiRenderContext> GLContext::CreateUiContext()
	{
		return CreateScope<ImGuiGLRenderContext>(m_window);
	}

	void GLContext::SetSwapInterval(int interval)
	{
		glfwSwapInterval(interval);
	}

	void GLContext::Init()
	{
		glfwMakeContextCurrent(m_window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			Assert(false, "Failed to init glad!");

#ifdef _DEBUG
		glUtils::InitOpenGLDebugMessageCallback();
#endif // _DEBUG


		GLint major = 0, minor = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		log::Info("OpenGL version: {}.{}", major, minor);
	}

	void GLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}