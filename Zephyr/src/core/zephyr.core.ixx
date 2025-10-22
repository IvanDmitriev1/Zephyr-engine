module;

#include <glad/glad.h>
#include <stdexcept>
#include <string>

export module zephyr.core;

export namespace zephyr
{
    inline void InitGLOrThrow()
    {
        if (!gladLoadGL())
            throw std::runtime_error("Failed to initialize OpenGL via GLAD");
    }

    inline std::string GLInfo()
    {
        const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
        const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
        const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
        return std::string("Vendor: ") + (vendor ? vendor : "?") +
            " | Renderer: " + (renderer ? renderer : "?") +
            " | Version: " + (version ? version : "?");
    }
}