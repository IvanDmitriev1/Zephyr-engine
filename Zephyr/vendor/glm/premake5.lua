project "glm"
    kind "StaticLib"
    language "C++"
    staticruntime "off"

    files {"glm/**.cpp", "glm/**.cppm", "glm/**.h", "glm/**.hpp"}

    defines
    {
        "GLM_GTC_INLINE_NAMESPACE",
        "GLM_EXT_INLINE_NAMESPACE",
        "GLM_GTX_INLINE_NAMESPACE"
    }