project "ZephyrEditor"

    includedirs
	{
		"%{wks.location}/Zephyr/src",
        "src",
		"%{IncludeDir.imgui}",
	}

    links {"Zephyr"}

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
		kind "WindowedApp"
		systemversion "latest"
