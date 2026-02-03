import Zephyr.Renderer.Platform.Window;

import Zephyr.Renderer.OpenGL.Window;

namespace Zephyr::Window
{
	IWindow* g_Window = nullptr;

	Scope<IWindow> CreateMainWindow(const WindowSpecification& spec)
	{
		auto window = CreateScope<OpenGL::GlWindow>(spec);
		g_Window = window.get();

		return window;
	}

	IWindow& GetMainWindow()
	{
		Assert(g_Window, "Window::GetMainWindow() called before Window::CreateMainWindow().");
		return *g_Window;
	}
}