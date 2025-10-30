project "ZephyrEditor"
    language "C++"

    includedirs
	{
		"%{wks.location}/Zephyr/src",
        "src",
        "%{IncludeDir.glfw}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
	}

    defines
    {
        "SPDLOG_COMPILED_LIB"
    }

    debugdir "%{prj.location}"
    links {"Zephyr"}

	files
    {
        "src/**.cpp",
        "src/**.hpp",
        "src/**.h",
        "src/**.ixx",
        "src/**.glsl",
    }
	
    filter "system:windows"
		kind "WindowedApp"
		systemversion "latest"