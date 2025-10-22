module;

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <stdexcept>
#include <string>
#include <cstdio>
#include <chrono>

module zephyr.app;

import glm;

namespace zephyr
{
    Application::Application(const char* windowTitle)
        : m_WindowTitle{ windowTitle }
    {
    }

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

            auto now = std::chrono::high_resolution_clock::now();
            [[maybe_unused]] float dt = std::chrono::duration<float>(now - prev).count();
            prev = now;

            int w, h; glfwGetFramebufferSize(window, &w, &h);
            glViewport(0, 0, w, h);
            glClearColor(0.10f, 0.10f, 0.12f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // rendering...
            glfwSwapBuffers(window);
        }

        glfwDestroyWindow(window);
        glfwTerminate();
    }
}