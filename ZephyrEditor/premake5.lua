project "ZephyrEditor"
    filter "system:windows"
		kind "WindowedApp"
		systemversion "latest"

    includedirs
	{
		"%{wks.location}/Zephyr/src",
        "src",
		"%{IncludeDir.imgui}",
        IncludeDir["reflectcpp"],
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

    removefiles
    {
        "**/Templates/**",
    }


    filter "files:**.glsl"
        buildaction "None"
