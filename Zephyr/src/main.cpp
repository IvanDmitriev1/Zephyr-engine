#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

import zephyr.app;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    zephyr::Application* app = zephyr::CreateApplication();
    app->Run();
    
    delete app;
    return 0;
}