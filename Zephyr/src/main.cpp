
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

import Zephyr.App;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	Zephyr::Application* app = Zephyr::CreateApplication();

	try
	{
		app->Run();
	}
	catch (...)
	{

	}

    delete app;
    return 0;
}