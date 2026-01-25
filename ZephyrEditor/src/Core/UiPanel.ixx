export module ZephyrEditor.UiPanel;

export import std;
export import <imgui.h>;

export namespace ZephyrEditor
{
	class UiPanel
	{
	public:
		virtual ~UiPanel() = default;

		// Lifecycle
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float deltaTime) {}
		void OnImGuiRender();

		virtual std::string_view GetTitle() const noexcept = 0;
		virtual ImGuiWindowFlags GetWindowFlags() const noexcept = 0;

		// Panel state
		inline bool IsOpen() const noexcept { return m_IsOpen; }
		inline void SetOpen(bool open) noexcept { m_IsOpen = open; }

		inline bool IsFocused() const noexcept { return m_IsFocused; }
		inline bool IsHovered() const noexcept { return m_IsHovered; }

	protected:
		virtual void OnDisplay() = 0;

	private:
		bool m_IsOpen = true;
		bool m_IsFocused = false;
		bool m_IsHovered = false;
	};
}