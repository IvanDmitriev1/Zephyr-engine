export module zephyr.renderer.IRendererAPI;

export import zephyr.events.ApplicationEvents;
export import zephyr.renderer.IFrameBuffer;
export import zephyr.renderer.DrawCommand;

export namespace zephyr
{
	class IRendererAPI
	{
	public:
		IRendererAPI() = default;
		virtual ~IRendererAPI() = default;

		IRendererAPI(const IRendererAPI&) = delete;
		IRendererAPI& operator=(const IRendererAPI&) = delete;

	public:
		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;

		virtual void SetDepthTest(bool enabled) = 0;
		virtual void SetScissorTest(bool enabled) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear(bool color, bool depth) = 0;


	public: // Drawing
		virtual void DrawIndexed(const IVertexArray& vao, PrimitiveTopology topology) = 0;
	};
}