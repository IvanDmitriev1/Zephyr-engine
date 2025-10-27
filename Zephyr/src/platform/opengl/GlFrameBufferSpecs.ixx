module;
#include <glad/glad.h> // for GL_* constants

export module zephyr.opengl.GlFrameBufferSpecs;

export import zephyr.renderer.FrameBufferSpecs;

export namespace zephyr
{
    class GlFrameBufferSpecs
    {
    public:
        static uint32_t ToGLInternal(FramebufferTextureFormat fmt)
        {
            switch (fmt)
            {
            case FramebufferTextureFormat::RGBA8:           return GL_RGBA8;
            case FramebufferTextureFormat::RED_INTEGER:     return GL_R32I;
            case FramebufferTextureFormat::DEPTH24STENCIL8: return GL_DEPTH24_STENCIL8;
            default: return GL_RGBA8;
            }
        }
        static uint32_t ToGLFormat(FramebufferTextureFormat fmt)
        {
            switch (fmt)
            {
            case FramebufferTextureFormat::RGBA8:       return GL_RGBA;
            case FramebufferTextureFormat::RED_INTEGER: return GL_RED_INTEGER;
            default: return GL_RGBA;
            }
        }
        static uint32_t ToGLType(FramebufferTextureFormat fmt)
        {
            switch (fmt)
            {
            case FramebufferTextureFormat::RGBA8:       return GL_UNSIGNED_BYTE;
            case FramebufferTextureFormat::RED_INTEGER: return GL_INT;
            default: return GL_UNSIGNED_BYTE;
            }
        }
        static bool IsDepth(FramebufferTextureFormat fmt)
        {
            return fmt == FramebufferTextureFormat::DEPTH24STENCIL8;
        }
    };
}
