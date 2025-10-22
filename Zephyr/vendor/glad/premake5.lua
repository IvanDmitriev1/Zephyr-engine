project "glad"
    kind "StaticLib"
    language "C"
    cdialect "C23"
    staticruntime "off"

    files { "include/**", "src/**" }
    includedirs {"include"}

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        optimize "On"