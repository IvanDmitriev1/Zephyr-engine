module;

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <stdexcept>
#include <string>
#include <cstdio>
#include <chrono>

export module zephyr.app;

import zephyr.core;

export namespace zephyr
{
	class Application
	{
	public:
		virtual ~Application() = default;

		Application(const char* windowTitle) 
			:m_WindowTitle{windowTitle}
		{}

	public:
		void Run();

	private:
		const char* m_WindowTitle;
	};

	void Application::Run()
	{
        if (!glfwInit())
            throw std::runtime_error("glfwInit failed");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(1280, 720, m_WindowTitle, nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            throw std::runtime_error("glfwCreateWindow failed");
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // vsync

        if (!gladLoadGL())
        {
            glfwDestroyWindow(window);
            glfwTerminate();
            throw std::runtime_error("gladLoadGL failed");
        }

        auto prev = std::chrono::high_resolution_clock::now();
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            // (optional) dt if you need it later
            auto now = std::chrono::high_resolution_clock::now();
            [[maybe_unused]] float dt = std::chrono::duration<float>(now - prev).count();
            prev = now;

            int w, h; glfwGetFramebufferSize(window, &w, &h);
            glViewport(0, 0, w, h);
            glClearColor(0.10f, 0.10f, 0.12f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // TODO: render your scene here

            glfwSwapBuffers(window);
        }

        glfwDestroyWindow(window);
        glfwTerminate();
	}


	export extern inline Application* CreateApplication();
}