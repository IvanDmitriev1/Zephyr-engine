export module ZephyrEditor.SceneHierarchyPanel;

export import ZephyrEditor.UiPanel;
import Zephyr.Scene.World;

using namespace Zephyr;

export namespace ZephyrEditor
{
	class SceneHierarchyPanel final : public UiPanel
	{
	public:
		SceneHierarchyPanel(World& world);

		inline std::string_view GetTitle() const noexcept { return "Scene Hierarchy"; }
		inline ImGuiWindowFlags GetWindowFlags() const noexcept override
		{
			return ImGuiWindowFlags_NoCollapse;
		}

		void OnDisplay() override;

	public:
		inline void SetSelectedEntity(Entity entity) { m_SelectedEntity = entity; }
		inline Entity GetSelectedEntity() const { return m_SelectedEntity; }

		std::function<void(Entity)> m_OnSelectionChanged;

	private:
		void DrawEntityNode(Entity entity);

	private:
		World& m_World;
		Entity m_SelectedEntity;
	};
}