export module Zephyr.Renderer.Platform.Window;

export import Zephyr.Renderer.Platform.IWindow;
export import Zephyr.Core.CoreTypes;

export namespace Zephyr::Window
{
	Scope<IWindow> CreateMainWindow(const WindowSpecification& spec);
	IWindow& GetMainWindow();
}
