module ZephyrEditor.SceneHierarchyPanel;

import Zephyr.Scene.Components.TransformComponent;
import Zephyr.Scene.Components.CameraComponent;
import Zephyr.Scene.Components.MeshComponent;

namespace ZephyrEditor
{
	SceneHierarchyPanel::SceneHierarchyPanel(World& world)
		:m_World(world)
	{
	}

	void SceneHierarchyPanel::OnDisplay()
	{
		auto entities = m_World.GetEntitiesWith<TransformComponent>();

		for (auto entity : entities)
		{
			DrawEntityNode(entity);
		}

		if (ImGui::BeginPopupContextWindow(nullptr, ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
			{
				
			}
			ImGui::EndPopup();
		}

	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		std::string label = std::format("Entity {}", entity.GetId());

		if (m_World.HasComponent<CameraComponent>(entity))
		{
			label = std::format("[Camera] {}", label);
		}
		else if (m_World.HasComponent<MeshComponent>(entity))
		{
			label = std::format("[Mesh] {}", label);
		}

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		if (m_SelectedEntity.IsValid() && m_SelectedEntity.GetId() == entity.GetId())
		{
			flags |= ImGuiTreeNodeFlags_Selected;
		}

		ImGui::TreeNodeEx(reinterpret_cast<void*>(static_cast<uintptr_t>(entity.GetId())),
						  flags,
						  "%s",
						  label.c_str());

		if (ImGui::IsItemClicked())
		{
			m_SelectedEntity = entity;
			m_OnSelectionChanged(entity);
		}

		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete"))
			{
				m_World.DestroyEntity(entity);
			}

			ImGui::EndPopup();
		}


	}
}