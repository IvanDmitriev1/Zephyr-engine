project "glm"
    kind "StaticLib"
    language "C++"
    staticruntime "off"

    files {"glm/**.cpp", "glm/**.h", "glm/**.hpp"}