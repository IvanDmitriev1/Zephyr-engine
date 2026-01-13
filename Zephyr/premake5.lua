project "Zephyr"
    kind "StaticLib"
    staticruntime "off"

    defines
    {
        "GLFW_INCLUDE_NONE",
    }

    includedirs
    {
        "src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.reflectcpp}",
    }

    libdirs { "%{LibraryDir.glfw}" }
    links { "glfw3", "imgui", "spdlog", "reflect-cpp" }

    files
    {
        "src/**.cpp",
        "src/**.hpp",
        "src/**.h",
        "src/**.ixx",
        "src/**.glsl",
    }
    removefiles { "**/vendor/**" }

    filter "files:**.glsl"
        buildaction "None"

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "Zephyr_PLATFORM_WINDOWS",
            "GLFW_EXPOSE_NATIVE_WIN32",
        }

    filter "platforms:Opengl"
        defines
        {
            "Zephyr_RENDERER=OpenGL",
            "ZEPHYR_RENDERER_OPENGL",
        }
        includedirs
        {
            "%{IncludeDir.glfw}",
            "%{IncludeDir.glad}",
            "%{IncludeDir.imguiOpengl}",
        }
        links
        {
            "opengl32.lib",
            "glad",
            "glm",
        }
