project "ZephyrEditor"
    language "C++"

    includedirs
	{
		"%{wks.location}/Zephyr/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
	}

    debugdir "%{prj.location}"
    links {"Zephyr"}

	files
    {
        "**.cpp",
        "**.hpp",
        "**.ixx",
        "**.glsl",
    }
	
    filter "system:windows"
		kind "WindowedApp"
		systemversion "latest"