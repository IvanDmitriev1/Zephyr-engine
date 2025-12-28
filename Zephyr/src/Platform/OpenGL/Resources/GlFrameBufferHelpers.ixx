module;

#include <glad/glad.h> 

export module Zephyr.Renderer.OpenGL.Resources.GlFrameBufferHelpers;

import Zephyr.Renderer.Resources.RenderPassTypes;

namespace Zephyr::RHI::OpenGL
{
    template <class B>
    concept RenderPassClearBackend =
        requires(const B & b, GLint i, const std::array<float, 4>&c, float d, GLint s)
    {
        {
            b.clearColor(i, c)
        } -> std::same_as<void>;
        {
            b.clearDepth(d)
        } -> std::same_as<void>;
        {
            b.clearStencil(s)
        } -> std::same_as<void>;
        {
            b.clearDepthStencil(d, s)
        } -> std::same_as<void>;
    };


    template <RenderPassClearBackend Backend>
    constexpr void ClearRenderPassImpl(const RenderPassDesc& rp, Backend&& backend)
    {
        // Color clears
        for (size_t i = 0; i < rp.Colors.size(); ++i)
        {
            if (rp.Colors[i].Load != LoadOp::Clear)
                continue;

            const std::array<float, 4> c = {
                rp.Colors[i].Clear.R,
                rp.Colors[i].Clear.G,
                rp.Colors[i].Clear.B,
                rp.Colors[i].Clear.A
            };

            backend.clearColor((GLint)i, c);
        }

        // Depth / stencil clears
        if (!rp.Depth)
            return;

        const bool clearDepth = (rp.Depth->Load == LoadOp::Clear);
        const bool clearStencil = rp.Depth->ClearStencilEnable;

        if (clearDepth && clearStencil)
        {
            backend.clearDepthStencil(rp.Depth->ClearDepth, (GLint)rp.Depth->ClearStencil);
        }
        else if (clearDepth)
        {
            backend.clearDepth(rp.Depth->ClearDepth);
        }
        else if (clearStencil)
        {
            backend.clearStencil((GLint)rp.Depth->ClearStencil);
        }
    }

    export void ClearDefaultFbo(const RenderPassDesc& rp)
    {
        //glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

        struct Backend
        {
            inline void clearColor(GLint i, const std::array<float, 4>& c) const
            {
                glClearBufferfv(GL_COLOR, i, c.data());
            }
            inline void clearDepth(float d) const
            {
                glClearBufferfv(GL_DEPTH, 0, &d);
            }
            inline void clearStencil(GLint s) const
            {
                glClearBufferiv(GL_STENCIL, 0, &s);
            }
            inline void clearDepthStencil(float d, GLint s) const
            {
                glClearBufferfi(GL_DEPTH_STENCIL, 0, d, s);
            }
        };

        ClearRenderPassImpl(rp, Backend{});
    }

    export void ClearNamedFbo(const RenderPassDesc& rp, GLuint fbo)
    {
        Assert(fbo != 0, "ClearNamedFbo: fbo must be a named framebuffer (non-zero)");

        struct Backend
        {
            GLuint fbo{};

            inline void clearColor(GLint i, const std::array<float, 4>& c) const
            {
                glClearNamedFramebufferfv(fbo, GL_COLOR, i, c.data());
            }
            inline void clearDepth(float d) const
            {
                glClearNamedFramebufferfv(fbo, GL_DEPTH, 0, &d);
            }
            inline void clearStencil(GLint s) const
            {
                glClearNamedFramebufferiv(fbo, GL_STENCIL, 0, &s);
            }
            inline void clearDepthStencil(float d, GLint s) const
            {
                glClearNamedFramebufferfi(fbo, GL_DEPTH_STENCIL, 0, d, s);
            }
        };

        ClearRenderPassImpl(rp, Backend{ fbo });
    }

}