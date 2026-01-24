export module ZephyrEditor.MenuBar;

export import std;

export namespace ZephyrEditor
{
	struct MenuItem
	{
		using CallbackFun = std::function<void()>;

		std::string Label;
		std::string Shortcut;
		CallbackFun Callback;

		bool IsEnabled = true;
		bool IsSeparator = false;
	};

	struct Menu
	{
		std::string Label;
		std::vector<MenuItem> Items;
	};

	class MenuBar final
	{
	public:
		MenuBar() = default;
		~MenuBar() = default;

	public:
		void Render();

		MenuBar& AddMenu(std::string label);
		MenuBar& AddItem(std::string label, MenuItem::CallbackFun callback, std::string shortcut = "");
		MenuBar& AddSeparator();

	private:
		std::vector<Menu> m_Menus;
	};
}