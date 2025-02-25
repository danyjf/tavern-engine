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

			for (const auto& [id, entity] : m_Scene.GetEntities())
			{
				if (!entity->GetParent())	// is a root entity
				{
					RenderEntityTree(entity.get());
				}
			}
		}
		ImGui::End();
	}

	void SceneWindow::RenderEntityTree(Tavern::Entity* entity) const
	{
		if (entity->GetComponentOfType<EditorCameraScript>())
		{
			return;
		}

		if (!entity->GetChildren().empty()						// has children
			&& ImGui::TreeNode(entity->GetName().c_str()))
		{
			for (Tavern::Entity* child : entity->GetChildren())
			{
				RenderEntityTree(child);
			}
			ImGui::TreePop();
		}
		else
		{
			ImGui::TreeNodeEx(entity->GetName().c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsItemClicked())
			{
				m_EventManager.QueueEvent<EntitySelectedEvent>(std::make_shared<EntitySelectedEvent>(entity));
			}
		}
	}

	void SceneWindow::OnProjectLoaded(std::shared_ptr<ProjectLoadedEvent> event)
	{
		TAVERN_INFO("LOAD SCENE WINDOW");
	}
}