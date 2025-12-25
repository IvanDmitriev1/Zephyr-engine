export module Zephyr.Renderer.Window;

export import Zephyr.Renderer.IWindow;
export import Zephyr.Core.CoreTypes;

export namespace Zephyr::Window
{
	Scope<IWindow> CreateMainWindow(const WindowSpecification& spec);
	IWindow& GetMainWindow();
}