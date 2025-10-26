project "ZephyrEditor"
    language "C++"

    includedirs
	{
		"%{wks.location}/Zephyr/src",
        "src",
        "%{IncludeDir.glfw}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
        "%{IncludeDir.imguiOpengl}",
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