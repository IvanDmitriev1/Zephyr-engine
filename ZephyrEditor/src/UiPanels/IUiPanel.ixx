export module ZephyrEditor.IUiPanel;

export import std;

export namespace ZephyrEditor
{
	class IUiPanel
	{
	public:
		virtual ~IUiPanel() = default;

		// Lifecycle
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnImGuiRender() = 0;

		// Panel state
		virtual std::string_view GetTitle() const noexcept = 0;
		virtual bool IsOpen() const noexcept { return m_IsOpen; }
		virtual void SetOpen(bool open) noexcept { m_IsOpen = open; }

		virtual bool IsFocused() const noexcept { return m_IsFocused; }

	protected:
		bool m_IsOpen = true;
		bool m_IsFocused = false;
	};
}