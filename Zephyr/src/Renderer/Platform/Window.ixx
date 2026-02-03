export module Zephyr.Renderer.Platform.Window;

import Zephyr.Renderer.Platform.IWindow;
import Zephyr.Core.CoreTypes;

export namespace Zephyr::Window
{
	Scope<IWindow> CreateMainWindow(const WindowSpecification& spec);
	IWindow& GetMainWindow();
}
