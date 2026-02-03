project "Zephyr"
    kind "StaticLib"
    staticruntime "off"

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
    removefiles { "src/Platform/**" }

    filter "system:windows"
        buildoptions { "/utf-8" }
        systemversion "latest"
        files
        {
            "src/Platform/Windows/**",
        }
        defines
        {
            "NOMINMAX"
        }

    filter "platforms:Opengl"
        files
        {
            "src/Platform/OpenGL/**",
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

    filter "files:**.glsl"
        buildaction "None"