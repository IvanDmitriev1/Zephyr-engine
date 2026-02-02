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

    filter "system:windows"
        buildoptions { "/utf-8" }
        systemversion "latest"
        defines
        {
            "NOMINMAX"
        }

    filter "platforms:Opengl"
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