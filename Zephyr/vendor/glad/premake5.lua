project "glad"
    kind "StaticLib"
    language "C"
    cdialect "C23"
    staticruntime "off"

    includedirs {"include"}
    files { "include/**", "src/**" }
