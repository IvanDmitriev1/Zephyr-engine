export module zephyr.app;

export import zephyr.core.coreTypes;
export import zephyr.renderer.IWindow;
export import zephyr.events.IEvent;

export namespace zephyr
{
    class Application
    {
    public:
        Application(const WindowSpecification& spec);
        virtual ~Application() = default;

        void Run();

    private:
        void OnEvent(const IEvent& e);

    private:
        const WindowSpecification m_windowSpec;
		Scope<IWindow> m_window;
        bool m_Running = true;
    };

    extern Application* CreateApplication();
}