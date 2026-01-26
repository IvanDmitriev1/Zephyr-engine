export module Zephyr.Renderer.RHI.RenderPassTypes;

export import Zephyr.Renderer.RHI.IFrameBuffer;
export import Zephyr.Renderer.Types.RenderPhase;
import std.compat;

export namespace Zephyr::RHI
{
    enum class LoadOp : uint8_t
    {
        Load, Clear, DontCare
    };
    enum class StoreOp : uint8_t
    {
        Store, DontCare
    };

    struct ClearColor
    {
        float R{}, G{}, B{}, A{ 1.f };
    };

    struct ColorAttachment
    {
        LoadOp Load = LoadOp::Clear;
        StoreOp Store = StoreOp::Store;
        ClearColor Clear{ 0.f, 0.f, 0.f, 1.f };
    };

    struct DepthAttachment
    {
        LoadOp Load = LoadOp::Clear;
        StoreOp Store = StoreOp::Store;
        float ClearDepth = 1.0f;

        uint32_t ClearStencil = 0;
        bool ClearStencilEnable = false;
    };

    struct RenderPassDesc
    {
        Ref<IFrameBuffer> Target{};
        std::span<const ColorAttachment> Colors{};
        std::optional<DepthAttachment> Depth{};

        std::string_view DebugName{};
    };

}