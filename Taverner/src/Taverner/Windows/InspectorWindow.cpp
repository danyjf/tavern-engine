#include <imgui.h>

#include <Tavern/Core/Engine.h>
#include <Tavern/Core/Log.h>
#include <Tavern/Scene/Entity.h>

#include "Taverner/Windows/InspectorWindow.h"
#include "Taverner/Events/EditorEvents.h"

namespace Taverner
{
	InspectorWindow::InspectorWindow(Tavern::EventManager& eventManager)
		: m_EventManager(eventManager),
		  m_EntitySelectedEvent(eventManager, std::bind(&InspectorWindow::OnEntitySelected, this, std::placeholders::_1))
	{
	}

	void InspectorWindow::Render()
	{
		if (ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_None))
		{

		}
		ImGui::End();
	}

	void InspectorWindow::OnEntitySelected(std::shared_ptr<EntitySelectedEvent> event)
	{
		m_SelectedEntity = event->GetEntity();
	}
}