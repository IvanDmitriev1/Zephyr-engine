project "Zephyr"
    kind "StaticLib"
    language "C++"
    staticruntime "off"

    defines
    {
        "GLFW_INCLUDE_NONE",
        "SPDLOG_COMPILED_LIB"
    }

    includedirs
    {
        "src",
        "%{IncludeDir.glm}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.imgui}",
    }

    links { "%{Library.glfw}", "imgui", "spdlog" }

    files
    {
        "src/**.cpp",
        "src/**.hpp",
        "src/**.h",
        "src/**.ixx",
        "src/**.glsl",
    }

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
