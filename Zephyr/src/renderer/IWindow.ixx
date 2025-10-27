export module zephyr.renderer.IWindow;

export import zephyr.renderer.IRendererAPI;
export import zephyr.renderer.IUiRenderContext;
export import zephyr.events.IEvent;

export namespace zephyr
{
	struct WindowSpecification
	{
		std::string Title;
		uint32_t Width = 1280;
		uint32_t Height = 720;
		bool IsResizeable = true;
		bool VSync = true;
	};

	class IWindow
	{
	public:
		IWindow() = default;
		virtual ~IWindow() = default;

		IWindow(const IWindow&) = delete;
		IWindow& operator=(const IWindow&) = delete;

	public:
		virtual void* GetNativeWindow() const = 0;
		virtual float GetTime() const = 0;
		virtual IRendererAPI& Gfx() const = 0;
		virtual IUiRenderContext& UiContext() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void Update() = 0;
		virtual bool ShouldClose() const = 0;
	};
}