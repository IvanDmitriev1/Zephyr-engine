module ZephyrEditor.InspectorPanel;

import Zephyr.Scene.Components.TransformComponent;
import Zephyr.Scene.Components.CameraComponent;
import Zephyr.Scene.Components.MeshComponent;


namespace ZephyrEditor
{
	InspectorPanel::InspectorPanel(World& world)
		:m_World(world)
	{
	}

	void InspectorPanel::OnImGuiRender()
	{
		if (!m_SelectedEntity.IsValid())
		{
			ImGui::TextDisabled("No entity selected");
		}
		else if (!m_World.IsAlive(m_SelectedEntity.GetId()))
		{
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid entity");
			m_SelectedEntity = Entity{};
		}
		else
		{
			DrawEntityInspector(m_SelectedEntity);
		}
	}

	void InspectorPanel::DrawEntityInspector(Entity entity)
	{
		ImGui::Text("Entity ID: %u", entity.GetId());
		ImGui::Separator();

		if (m_World.HasComponent<TransformComponent>(entity))
		{
			DrawTransformComponent(entity);
		}
	}

	void InspectorPanel::DrawTransformComponent(Entity entity)
	{
		if (!ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
			return;

		auto& transform = m_World.GetComponent<TransformComponent>(entity);
		bool changed = false;

		ImGui::Indent();
		changed |= ImGui::DragFloat3("Position", &transform.Position.x, 0.1f);

		glm::vec3 eulerAngles = transform.GetEulerAngles();
		if (ImGui::DragFloat3("Rotation", &eulerAngles.x, 1.0f))
		{
			transform.SetEulerAngles(eulerAngles);
			changed = true;
		}

		changed |= ImGui::DragFloat3("Scale", &transform.Scale.x, 0.01f, 0.001f, 100.0f);

		if (changed)
		{
			transform.IsDirty = true;
		}

		if (m_World.HasComponent<TransformRuntimeComponent>(entity))
		{
			auto& runtime = m_World.GetComponent<TransformRuntimeComponent>(entity);

			ImGui::Separator();
			ImGui::TextDisabled("Runtime (Read-Only)");
			ImGui::Text("World Pos: (%.2f, %.2f, %.2f)",
						runtime.WorldPosition.x,
						runtime.WorldPosition.y,
						runtime.WorldPosition.z
			);
		}

		ImGui::Unindent();
	}
}