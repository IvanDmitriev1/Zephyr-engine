output_dir = '%{cfg.buildcfg}_%{cfg.system}'
include "Dependencies.lua"

workspace "Zephyr"
    architecture "x86_64"
    language "C++"
    cppdialect "C++23"

    startproject "ZephyrEditor"

    configurations { "Debug", "Release" }
    platforms { "Opengl" }
    flags { "MultiProcessorCompile" }

    debugdir    ('.bin/'	 .. output_dir .. '/%{prj.name}')
    targetdir   ('.bin/'	 .. output_dir .. '/%{prj.name}')
    objdir      ('.bin_int/' .. output_dir .. '/%{prj.name}')

    filter "configurations:Debug"
        defines { "_DEBUG" }
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        optimize "Speed"
        runtime "Release"
        linktimeoptimization "On"

    filter "system:windows"
        buildoptions { "/utf-8" }
        toolset "v145"


    removefiles { "**/vendor/**" }

group "Dependencies"
	include "Zephyr/vendor/glad"
	include "Zephyr/vendor/glm"
    include "Zephyr/vendor/spdlog"
    include "Zephyr/vendor/imgui"
group ""

include "Zephyr"
include "ZephyrEditor"