export module zephyr.renderer.DrawCommand;

export import zephyr.renderer.IShader;
export import zephyr.renderer.IVertexArray;

export namespace zephyr
{
    enum class PrimitiveTopology
    {
        Triangles,
        Lines
    };

    struct DrawCommand
    {
        Ref<IShader> Shader;
        Ref<IVertexArray> VertexArray;
        PrimitiveTopology Topology = PrimitiveTopology::Triangles;

        glm::mat4 Transform{ 1.0f };
    };
}