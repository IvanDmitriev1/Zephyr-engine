export module zephyr.app;

export import zephyr.core.coreTypes;
export import zephyr.core.LayerStack;
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

    protected:
        LayerStack& GetLayerStack()
        {
            return m_LayerStack;
        }

        IWindow& GetWindow()
        {
            return *m_window;
		}

    private:
        void OnEvent(const IEvent& e);

    private:
        const WindowSpecification m_windowSpec;
		Scope<IWindow> m_window;
		LayerStack m_LayerStack;
        bool m_Running = true;
		bool m_Minimized = false;
    };

    extern Application* CreateApplication();
}