export module Zephyr.Renderer.Platform.IWindow;

export import Zephyr.Renderer.Platform.WindowTypes;
export import zephyr.events.IEvent;
import Zephyr.Renderer.Platform.IUiRenderContext;
import Zephyr.Core.CoreTypes;
import Zephyr.Renderer.Types.CommonTypes;

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
		virtual Extent2D GetSize() const noexcept = 0;

		virtual void PollEvents() = 0;
		virtual bool ShouldClose() const = 0;
		virtual void SwapBuffers() = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
	};
}
