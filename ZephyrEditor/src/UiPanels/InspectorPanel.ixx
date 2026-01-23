export module ZephyrEditor.InspectorPanel;

export import ZephyrEditor.UiPanel;
import Zephyr.Scene.World;

using namespace Zephyr;

export namespace ZephyrEditor
{
	class InspectorPanel final : public UiPanel
	{
	public:
		InspectorPanel(World& world);

		inline std::string_view GetTitle() const noexcept { return "Inspector"; }
		inline ImGuiWindowFlags GetWindowFlags() const noexcept override
		{
			return ImGuiWindowFlags_NoCollapse;
		}

		void OnImGuiRender() override;

	public:
		inline void SetSelectedEntity(Entity entity) { m_SelectedEntity = entity; }
		inline Entity GetSelectedEntity() const { return m_SelectedEntity; }

	private:
		void DrawEntityInspector(Entity entity);
		void DrawTransformComponent(Entity entity);


	private:
		World& m_World;

		Entity m_SelectedEntity;
	};

}