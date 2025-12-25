project "ZephyrEditor"
    language "C++"

    includedirs
	{
		"%{wks.location}/Zephyr/src",
        "src",
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

    filter "files:**.glsl"
        buildaction "None"
	
    filter "system:windows"
		kind "WindowedApp"
		systemversion "latest"