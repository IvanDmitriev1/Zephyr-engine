output_dir = '%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}_%{cfg.platform}'
include "Dependencies.lua"

workspace "Zephyr"
    architecture "x86_64"
    language "C++"
    cppdialect "C++23"
    defines { "SPDLOG_COMPILED_LIB" }

    startproject "ZephyrEditor"

    configurations { "Debug", "Release", "Dist" }
    platforms { "Opengl" }
    flags { "MultiProcessorCompile" }

    debugdir "%{prj.location}"
    targetdir   ('.bin/'	 .. output_dir .. '/%{prj.name}')
    objdir      ('.bin_int/' .. output_dir .. '/%{prj.name}')

    filter "configurations:Debug"
        defines { "_DEBUG" }
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        symbols "On"
        optimize "Speed"
        runtime "Release"
        linktimeoptimization "On"

    filter "configurations:Dist"
        optimize "Full"
        runtime "Release"
        linktimeoptimization "On"

    filter "system:windows"
        buildoptions { "/utf-8" }
        defines
		{
			"ZEPHYR_PLATFORM_WINDOWS",
		}

    filter "action:vs2022"
        toolset "v145"

group "Dependencies"
	include "Zephyr/vendor/glad"
	include "Zephyr/vendor/glm"
    include "Zephyr/vendor/spdlog"
    include "Zephyr/vendor/imgui"
group ""

include "Zephyr"
include "ZephyrEditor"
include "Sandbox"
