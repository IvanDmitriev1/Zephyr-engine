export module Zephyr.Renderer.RHI.Types.PipelineTypes;

export import Zephyr.Renderer.RHI.Types.TextureTypes;
export import Zephyr.Renderer.RHI.Types.VertexLayout;
export import Zephyr.Renderer.RHI.Interfaces.IShader;
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

    enum class PolygonMode : uint8_t
    {
        Fill,
        Wireframe,
        Point
    };


    struct RasterizerState
    {
        CullMode Cull = CullMode::Back;
        FrontFace Face = FrontFace::CounterClockwise;
        PolygonMode Polygon = PolygonMode::Fill;

        bool DepthClampEnable = false;
    };

    enum class CompareOp : uint8_t
    {
        Never, 
        Less,
        Equal,
        LessEqual,
        Greater,
        NotEqual,
        GreaterEqual,
        Always
    };

    struct DepthStencilState
    {
		CompareOp DepthCompare = CompareOp::LessEqual;
        bool DepthTestEnable = true;
        bool DepthWriteEnable = true;
        bool StencilTestEnable = false;
    };

    struct BlendState
    {
        bool Enable = false;
    };

    struct GraphicsPipelineDesc
    {
        Ref<IShader> Shader{};
        PrimitiveTopology Topology = PrimitiveTopology::Triangles;

        RasterizerState Rasterizer{};
        DepthStencilState Depth{};
        BlendState Blend{};

		TextureFormat ColorFormat{};
        TextureFormat DepthFormat = TextureFormat::DEPTH24STENCIL8;

        uint32_t SampleCount = 1; // MSAA
        
        std::string_view DebugName{};
    };
}