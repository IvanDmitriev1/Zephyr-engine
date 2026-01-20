export module ZephyrEditor.UiPanelHost;

export import ZephyrEditor.UiPanel;
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
		void Render();

		template<typename TUiPanel, typename ... Args>
			requires(std::is_base_of_v<UiPanel, TUiPanel>)
		void Add(Args&& ... args);

		UiPanel* Find(std::string_view id) noexcept;
		bool Remove(std::string_view id);

	private:
		void OnAdd(Scope<UiPanel> panel) noexcept;
		Iterator FindIt(std::string_view id) noexcept;

	private:
		PanelList m_Panels;
	};

	template<typename TUiPanel, typename ...Args>
		requires(std::is_base_of_v<UiPanel, TUiPanel>)
	void UiPanelHost::Add(Args && ...args)
	{
		auto panel = CreateScope<TUiPanel>(std::forward<Args>(args)...);
		OnAdd(std::move(panel));
	}
}