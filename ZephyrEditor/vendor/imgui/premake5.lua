project "imgui"
    kind "StaticLib"
	language "C++"
    staticruntime "off"

    includedirs { "src", "%{IncludeDir.glfw}"}

    files
	{
        "src/*"
	}

    filter "platforms:Opengl"
        files
	{
        "platform/opengl/*"
	}