export module zephyr.app;

export namespace zephyr
{
    class Application
    {
    public:
        Application(const char* windowTitle);
        virtual ~Application() = default;

        void Run();
    private:
        const char* m_WindowTitle;
    };

    extern Application* CreateApplication();
}