project "reflect-cpp"
    kind "StaticLib"
    language "C++"
    staticruntime "off"
	
    includedirs
    {
        "reflect-cpp/include",
        "vendor"
    }

    files
    {
        "vendor/**",
        "reflect-cpp/include/**",
        "reflect-cpp/src/reflectcpp.cpp",
        "reflect-cpp/src/reflectcpp_toml.cpp",
    }