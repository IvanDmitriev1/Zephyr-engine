project "Zephyr"
    kind "StaticLib"
    language "C++"
    staticruntime "off"

    defines { "GLFW_INCLUDE_NONE" }
    includedirs { "src", "%{IncludeDir.glfw}", "%{IncludeDir.glm}",}
    links { "%{Library.glfw}" }

    files
    {
        "**.cpp",
        "**.hpp",
        "**.ixx",
        "**.glsl",
        "**/vendor/glfw/**",
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
        }
        links
        {
            "opengl32.lib",
            "glad",
        }
