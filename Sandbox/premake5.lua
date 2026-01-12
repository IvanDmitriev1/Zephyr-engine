	project "Sandbox"
		language "C++"
		configurations { "EditorDebug", "EditorRelease", "Dist" }

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

	filter "configurations:EditorDebug or configurations:EditorRelease"
		kind "SharedLib"

	filter "configurations:EditorDebug"
		defines { "_DEBUG" }
		symbols "On"
		runtime "Debug"

	filter "configurations:EditorRelease"
		optimize "Speed"
		runtime "Release"
		linktimeoptimization "On"

	filter "configurations:Dist"
		optimize "Full"
		runtime "Release"
		linktimeoptimization "On"
