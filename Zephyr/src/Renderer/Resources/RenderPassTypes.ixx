export module Zephyr.Renderer.Resources.RenderPassTypes;

export import Zephyr.Renderer.Core.IFrameBuffer;
import std.compat;

export namespace Zephyr::RHI
{
    struct RenderPassDesc
    {
        Ref<IFrameBuffer> Target{};

        bool ClearColor = true;
        glm::vec4 Color{};

        bool ClearDepth = false;
        float Depth = 1.0f;

        bool ClearStencil = false;
        uint32_t Stencil = 0;
    };

}