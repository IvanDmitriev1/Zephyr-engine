export module Zephyr.Renderer.IWindow;

export import Zephyr.Renderer.WindowTypes;
export import Zephyr.Renderer.Ui.IUiRenderContext;
export import Zephyr.Core.CoreTypes;
export import zephyr.events.IEvent;
export import glm;

export namespace Zephyr
{
	class IWindow
	{
	public:
		virtual ~IWindow() = default;

	public:
		virtual Scope<IUiRenderContext> CreateUiContext() const noexcept = 0;

		virtual void* GetNativeHandle() const noexcept = 0;
		virtual float GetTime() const noexcept = 0;
		virtual glm::ivec2 GetSize() const noexcept = 0;

		virtual void PollEvents() = 0;
		virtual bool ShouldClose() const = 0;
		virtual void SwapBuffers() = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
	};
}