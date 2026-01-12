	project "Sandbox"
		language "C++"

	includedirs
	{
		"%{wks.location}/Zephyr/src",
		"src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
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

	filter "configurations:Dist"
		optimize "Full"
		runtime "Release"
		linktimeoptimization "On"
