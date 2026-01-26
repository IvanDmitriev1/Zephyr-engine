export module Zephyr.App;

export import Zephyr.Core.CoreTypes;
export import Zephyr.Core.LayerStack;
export import zephyr.events.IEvent;
export import zephyr.logging.LoggerBuilder;
export import zephyr.logging.LogBuffer;

export import Zephyr.Renderer.RHI.Device;
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
		virtual void OnInit() = 0;
		virtual void OnUpdate(float dt) = 0;
		virtual void OnRender() = 0;
		virtual void OnUiRender() = 0;
		virtual void OnEvent(IEvent& e) = 0;

    private:
        void ConfigureLogging();
		void OnEventDispatch(IEvent& e);

    private:
        Scope<IWindow> m_window;
        Scope<IUiRenderContext> m_uiRenderContext;
		Ref<LogBuffer> m_LogBuffer;

        bool m_Running = true;
		bool m_Minimized = false;
    };

    extern Application* CreateApplication();
}