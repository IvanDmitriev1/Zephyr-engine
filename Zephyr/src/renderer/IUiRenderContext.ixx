export module zephyr.renderer.IUiRenderContext;

export import zephyr.events.IEvent;

export namespace zephyr
{
	class IUiRenderContext
	{
	public:
		IUiRenderContext() = default;
		virtual ~IUiRenderContext() = default;

		IUiRenderContext(const IUiRenderContext&) = delete;
		IUiRenderContext& operator=(const IUiRenderContext&) = delete;

	public:
		virtual void OnEvent(const IEvent& e) = 0;
		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;
	};
}