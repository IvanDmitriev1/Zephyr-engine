export module zephyr.renderer.IRendererAPI;

export import zephyr.events.ApplicationEvents;
export import zephyr.renderer.IFrameBuffer;

export namespace zephyr
{
	class IRendererAPI
	{
	public:
		IRendererAPI() = default;
		virtual ~IRendererAPI() = default;

		IRendererAPI(const IRendererAPI&) = delete;
		IRendererAPI& operator=(const IRendererAPI&) = delete;

	public:
		virtual IFrameBuffer& GetFrameBuffer() const = 0;

	public:
		virtual void OnEvent(const ApplicationEvent& e) = 0;
		virtual void StartOfTheFrame() = 0;
		virtual void EndOfTheFrame() = 0;
	};
}