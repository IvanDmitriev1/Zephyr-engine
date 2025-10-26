project "ZephyrEditor"
    language "C++"

    includedirs
	{
		"%{wks.location}/Zephyr/src",
        "src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
	}

    debugdir "%{prj.location}"
    links {"Zephyr", "imgui"}

	files
    {
        "**.cpp",
        "**.hpp",
        "**.h",
        "**.ixx",
        "**.glsl",
    }
	
    filter "system:windows"
		kind "WindowedApp"
		systemversion "latest"