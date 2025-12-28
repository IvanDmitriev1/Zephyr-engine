export module zephyr.app;

export import Zephyr.Core.CoreTypes;
export import zephyr.core.LayerStack;
export import zephyr.events.IEvent;
export import zephyr.logging.LoggerBuilder;
export import zephyr.logging.LogBuffer;

export import Zephyr.Renderer.Core.Device;
export import Zephyr.Renderer.Window;

import Zephyr.Renderer.Shader.ShaderLoader;

export namespace Zephyr
{
    class Application
    {
    public:
        Application(const WindowSpecification& spec);
        virtual ~Application() = default;

        void Run();

    protected:
        LayerStack& GetLayerStack();
        LogBuffer& GetLogBuffer();

        virtual void ConfigureEngineLogger(LoggerBuilder& builder) { }
        virtual void ConfigureAppLogger(LoggerBuilder& builder) { }

    private:
        void ConfigureLogging();

        void OnEvent(IEvent& e);

    private:
		LayerStack m_LayerStack;
        Scope<IWindow> m_window;
        Scope<IUiRenderContext> m_uiRenderContext;
        Ref<RHI::ISwapchain> m_swapchain;
        Ref<LogBuffer> m_LogBuffer;
        bool m_Running = true;
		bool m_Minimized = false;
    };

    extern Application* CreateApplication();
}