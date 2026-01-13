	project "Sandbox"
		language "C++"

	includedirs
	{
		"%{wks.location}/Zephyr/src",
		"src",
		"%{IncludeDir.imgui}",
	}

	defines
    {
        "ZEPHYR_MODULE_BUILD"
    }

	links { "Zephyr" }

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

	filter "configurations:Debug or configurations:Release"
		kind "SharedLib"
