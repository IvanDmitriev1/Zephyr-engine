project "spdlog"
    kind "StaticLib"
    language "C++"
    staticruntime "off"

    defines { "SPDLOG_COMPILED_LIB" }

    includedirs
    {
        "include",
    }

    files
    {
        "include/**",
        "src/**"
    }