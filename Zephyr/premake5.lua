project "Zephyr"
    kind "StaticLib"
    language "C++"
    staticruntime "off"

    defines { "GLFW_INCLUDE_NONE" }

    includedirs
    {
        "src",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.imgui}",
    }

    links { "%{Library.glfw}", "imgui" }

    files
    {
        "**.cpp",
        "**.hpp",
        "**.h",
        "**.ixx",
        "**.glsl",
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
