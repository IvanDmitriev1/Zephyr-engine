export module ZephyrEditor.UiPanelHost;

export import ZephyrEditor.UiPanel;
export import ZephyrEditor.MenuBar;
export import Zephyr.Core.CoreTypes;

using namespace Zephyr;

export namespace ZephyrEditor
{
	class UiPanelHost final
	{
		using PanelList = std::vector<Scope<UiPanel>>;
		using Iterator = PanelList::iterator;
		using ConstIterator = PanelList::const_iterator;

	public:	
		UiPanelHost() = default;
		~UiPanelHost();

		UiPanelHost(const UiPanelHost&) = delete;
		UiPanelHost& operator=(const UiPanelHost&) = delete;

	public:
		void OnUpdate(float deltaTime);
		void OnImGuiRender();

		template<typename TUiPanel, typename ... Args>
			requires(std::is_base_of_v<UiPanel, TUiPanel>)
		TUiPanel& Add(Args&& ... args)
		{
			auto panel = CreateScope<TUiPanel>(std::forward<Args>(args)...);
			TUiPanel* ptr = panel.get();

			OnAdd(std::move(panel));
			return *ptr;
		}

		UiPanel* Find(std::string_view id) noexcept;
		UiPanel& Get(std::string_view id);
		bool Remove(std::string_view id);

	public:
		inline MenuBar& GetMenuBar() { return m_MenuBar; }

	private:
		void OnAdd(Scope<UiPanel> panel) noexcept;
		Iterator FindIt(std::string_view id) noexcept;

	private:
		void RenderDockspaceRoot();
		void BuildDefaultDockLayout(ImGuiID dock_main_id);
		
	private:
		PanelList m_Panels;
		MenuBar m_MenuBar;
	};
}