project "glm"
    kind "StaticLib"
    language "C++"
    staticruntime "off"

    files {"glm/**.cpp", "glm/**.cppm", "glm/**.h", "glm/**.hpp"}