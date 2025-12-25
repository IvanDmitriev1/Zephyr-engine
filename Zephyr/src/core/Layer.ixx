export module zephyr.core.Layer;

export import zephyr.events.IEvent;

export namespace Zephyr
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
		virtual void OnAttach()
		{
		}
		virtual void OnDetach()
		{
		}

		virtual void OnEvent(const IEvent& event)
		{
		}
		virtual void OnUpdate(float ts)
		{
		}
		virtual void OnRender()
		{
		}
		virtual void OnUi()
		{
		}

		std::string_view GetName()
		{
			return m_Name;
		}

	private:
		const std::string m_Name;
	};
}