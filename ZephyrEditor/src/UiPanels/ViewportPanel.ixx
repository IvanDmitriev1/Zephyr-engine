export module ZephyrEditor.ViewportPanel;

export import ZephyrEditor.IUiPanel;

export namespace ZephyrEditor
{
	class ViewportPanel final : public IUiPanel
	{
	public:
		ViewportPanel(std::string_view title);

	private:
		std::string m_Title;

	};
}