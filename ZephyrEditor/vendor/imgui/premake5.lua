project "imgui"
    kind "StaticLib"
	language "C++"
    staticruntime "off"

    includedirs
    {
        "%{IncludeDir.glfw}",
        "./include",
    }

    files
	{
        "include/*"
	}

    filter "platforms:Opengl"
        files
	    {
            "platform/opengl/*"
	    }