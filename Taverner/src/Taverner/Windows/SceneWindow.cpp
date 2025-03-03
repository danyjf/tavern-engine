#include <imgui.h>

#include <Tavern/Core/Log.h>
#include <Tavern/Scene/Scene.h>
#include <Tavern/Scene/Entity.h>
#include <Tavern/Events/EventManager.h>

#include "Taverner/Windows/SceneWindow.h"
#include "Taverner/Core/EditorCamera.h"
#include "Taverner/Events/EditorEvents.h"

namespace Taverner
{
	SceneWindow::SceneWindow(Tavern::Scene& scene, Tavern::EventManager& eventManager)
		: m_Scene(scene),
		  m_EventManager(eventManager),
		  m_ProjectLoadedEvent(eventManager, std::bind(&SceneWindow::OnProjectLoaded, this, std::placeholders::_1))
	{
	}

	void SceneWindow::Render()
	{
		if (ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_None))
		{
			if (ImGui::Button("+"))
			{
				TAVERN_INFO("Add Entity");
			}

			RenderEntityTree(m_Scene.GetRoot());
		}
		ImGui::End();
	}

	void SceneWindow::RenderEntityTree(Tavern::Entity* entity)
	{
		//ImGui::ShowDemoWindow();

		std::string label = entity->GetName() + "##" + std::to_string(entity->GetID()); 
		ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_SpanAvailWidth;
		if (m_SelectedEntityID == entity->GetID())
		{
			nodeFlags |= ImGuiTreeNodeFlags_Selected;
		}

		if (!entity->GetChildren().empty())
		{
			nodeFlags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
			bool nodeOpen = ImGui::TreeNodeEx(label.c_str(), nodeFlags);
			if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			{
				m_SelectedEntityID = entity->GetID();
				m_EventManager.QueueEvent<EntitySelectedEvent>(std::make_shared<EntitySelectedEvent>(entity->GetID()));
			}
			if (nodeOpen)
			{
				for (Tavern::Entity* child : entity->GetChildren())
				{
					RenderEntityTree(child);
				}
				ImGui::TreePop();
			}
		}
		else
		{
			nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
			ImGui::TreeNodeEx(label.c_str(), nodeFlags);
			if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			{
				m_SelectedEntityID = entity->GetID();
				m_EventManager.QueueEvent<EntitySelectedEvent>(std::make_shared<EntitySelectedEvent>(entity->GetID()));
			}
		}
	}

	void SceneWindow::OnProjectLoaded(std::shared_ptr<ProjectLoadedEvent> event)
	{
		TAVERN_INFO("LOAD SCENE WINDOW");
	}
}