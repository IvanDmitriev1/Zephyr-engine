export module zephyr.renderer.IGraphicsContext;

export import zephyr.core.coreTypes;
export import zephyr.renderer.IRendererAPI;
export import zephyr.renderer.IUiRenderContext;

export namespace zephyr
{
	class IGraphicsContext
	{
	public:
		IGraphicsContext() = default;
		virtual ~IGraphicsContext() = default;

		IGraphicsContext(const IGraphicsContext&) = delete;
		IGraphicsContext& operator=(const IGraphicsContext&) = delete;

	public:
		virtual Scope<IUiRenderContext> CreateUiContext() = 0;
		virtual void SetSwapInterval(int interval) = 0;

	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}