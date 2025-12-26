export module Zephyr.Renderer.Resources.PipelineTypes;

export import Zephyr.Renderer.Resources.TextureTypes;
export import Zephyr.Renderer.Resources.VertexLayout;
export import Zephyr.Renderer.Core.IShader;
export import Zephyr.Core.CoreTypes;

export namespace Zephyr::RHI
{
    enum class PrimitiveTopology : uint8_t
    {
        Points,
        Lines,
        LineStrip,
        Triangles,
        TriangleStrip
    };

    enum class CullMode : uint8_t
    {
        None,
        Front,
        Back,
        FrontAndBack
    };

    enum class FrontFace : uint8_t
    {
        Clockwise,
        CounterClockwise
    };

    struct RasterizerState
    {
        CullMode CullMode = CullMode::Back;
        FrontFace FrontFace = FrontFace::CounterClockwise;
        bool DepthClampEnable = false;
        bool ScissorTestEnable = false;
        float LineWidth = 1.0f;
    };

    struct PipelineDesc
    {
        Ref<IShader> Shader{};
        VertexLayout VertexLayout{};
        PrimitiveTopology Topology{ PrimitiveTopology::Triangles };
        RasterizerState rasterizerState{};

        std::string_view DebugName{};
    };
}