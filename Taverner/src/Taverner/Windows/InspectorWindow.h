#pragma once

#include <imgui.h>

#include <Tavern/Core/Engine.h>

namespace Taverner
{
	class EntitySelectedEvent;

	class InspectorWindow
	{
	public:
		InspectorWindow(Tavern::EventManager& eventManager);

		void Render();

	private:
		Tavern::EventManager& m_EventManager;
		Tavern::Entity* m_SelectedEntity = nullptr;

		Tavern::EventListener<EntitySelectedEvent> m_EntitySelectedEvent;

		void OnEntitySelected(std::shared_ptr<EntitySelectedEvent> event);
	};
}