export module Zephyr.Core.Layer;

export import zephyr.events.IEvent;

export namespace Zephyr
{
	class Layer
	{
	public:
		explicit Layer(std::string_view name)
			:m_Name(name)
		{}

		virtual ~Layer() = default;

		Layer(const Layer&) = delete;
		Layer& operator=(const Layer&) = delete;

	public:
		virtual void OnAttach(){}
		virtual void OnDetach(){}

		virtual void OnEvent(IEvent& event) {}
		virtual void OnUpdate(float ts) {}
		virtual void OnRender() {}
		virtual void OnUiRender() {}

		std::string_view GetName()
		{
			return m_Name;
		}

		bool IsEnabled() const noexcept
		{
			return m_Enabled;
		}

		void SetEnabled(bool enabled) noexcept
		{
			m_Enabled = enabled;
		}

	private:
		const std::string m_Name;
		bool m_Enabled = true;
	};
}