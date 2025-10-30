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
        "%{IncludeDir.glfw}",
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
            "Zephyr_RENDERER=Opengl",
        }
        includedirs
        {
            "%{IncludeDir.glm}",
            "%{IncludeDir.glad}",
            "%{IncludeDir.imguiOpengl}",
        }
        links
        {
            "opengl32.lib",
            "glad",
            "glm",
        }
