export module zephyr.app;

export import zephyr.core.coreTypes;
export import zephyr.core.LayerStack;
export import zephyr.renderer.IWindow;
export import zephyr.events.IEvent;
export import zephyr.logging.LoggerBuilder;
export import zephyr.logging.BufferedLogSink;

export namespace zephyr
{
    class Application
    {
    public:
        Application(const WindowSpecification& spec);
        virtual ~Application() = default;

        void Run();

    protected:
        LayerStack& GetLayerStack();
        IWindow& GetWindow();
        BufferedLogSink<>& GetLogSink();

        virtual void ConfigureEngineLogger(LoggerBuilder& builder) { }
        virtual void ConfigureAppLogger(LoggerBuilder& builder) { }

    private:
        void ConfigureLogging();

        void OnEvent(const IEvent& e);

    private:
        const WindowSpecification m_windowSpec;
		Scope<IWindow> m_window;
		LayerStack m_LayerStack;
        Ref<BufferedLogSink<>> m_BufferedLogSink;
        bool m_Running = true;
		bool m_Minimized = false;
    };

    extern Application* CreateApplication();
}