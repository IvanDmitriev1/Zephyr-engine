project "reflect-cpp"
    kind "StaticLib"
    language "C++"
    staticruntime "off"
	
    includedirs
    {
        IncludeDir["reflectcpp"],
    }

    files
    {
        "vendor/**",
        "reflect-cpp/include/**",
        "reflect-cpp/src/reflectcpp.cpp",
        "reflect-cpp/src/reflectcpp_toml.cpp",
    }