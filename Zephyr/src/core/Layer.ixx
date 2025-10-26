export module zephyr.core.Layer;

export import zephyr.events.IEvent;

export namespace zephyr
{
	class Layer
	{
	public:
		Layer(std::string_view name)
			:m_Name(name)
		{

		}

		virtual ~Layer() = default;

		Layer(const Layer&) = delete;
		Layer& operator=(const Layer&) = delete;

	public:
		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;

		virtual void OnEvent(const IEvent& event) = 0;
		virtual void OnUpdate(float ts) = 0;
		virtual void OnRender() = 0;

		std::string_view GetName()
		{
			return m_Name;
		}

	private:
		const std::string m_Name;
	};
}