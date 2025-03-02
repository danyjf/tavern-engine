#include <imgui.h>

#include <Tavern/Core/Engine.h>
#include <Tavern/Core/Log.h>
#include <Tavern/Scene/Entity.h>
#include <Tavern/Components/TransformComponent.h>
#include <Tavern/Components/CameraComponent.h>
#include <Tavern/Components/LightComponent.h>
#include <Tavern/Components/MeshComponent.h>
#include <Tavern/Components/ScriptComponent.h>

#include "Taverner/ComponentInspectors/TransformComponentInspector.h"
#include "Taverner/ComponentInspectors/CameraComponentInspector.h"
#include "Taverner/ComponentInspectors/LightComponentInspector.h"
#include "Taverner/ComponentInspectors/MeshComponentInspector.h"
#include "Taverner/ComponentInspectors/ScriptComponentInspector.h"
#include "Taverner/Events/EditorEvents.h"
#include "Taverner/Windows/InspectorWindow.h"

namespace Taverner
{
	InspectorWindow::InspectorWindow(Tavern::EventManager& eventManager, Tavern::Scene& scene)
		: m_EventManager(eventManager),
		  m_Scene(scene),
		  m_EntitySelectedEvent(eventManager, std::bind(&InspectorWindow::OnEntitySelected, this, std::placeholders::_1))
	{
		RegisterComponentInspector<Tavern::TransformComponent, TransformComponentInspector>();
		RegisterComponentInspector<Tavern::CameraComponent, CameraComponentInspector>();
		RegisterComponentInspector<Tavern::LightComponent, LightComponentInspector>();
		RegisterComponentInspector<Tavern::MeshComponent, MeshComponentInspector>();
		RegisterComponentInspector<Tavern::ScriptComponent, ScriptComponentInspector>();
	}

	void InspectorWindow::Render()
	{
		if (ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_None))
		{
			Tavern::Entity* selectedEntity = m_Scene.GetEntity(m_SelectedEntityID);
			if (selectedEntity)
			{
				for (const auto& component : selectedEntity->GetComponents())
				{
					// Check if the component is a ScriptComponent
					if (dynamic_cast<Tavern::ScriptComponent*>(component.get()))
					{
						m_ComponentInspectorRegistry.at(typeid(Tavern::ScriptComponent))->Render(component.get());
					}
					else
					{
						m_ComponentInspectorRegistry.at(typeid(*component))->Render(component.get());
					}
				}
			}
		}
		ImGui::End();
	}

	void InspectorWindow::OnEntitySelected(std::shared_ptr<EntitySelectedEvent> event)
	{
		m_SelectedEntityID = event->GetEntityID();
	}
}