#pragma once

#include <imgui.h>
#include <Tavern/Core/Engine.h>

#include "Taverner/ComponentInspectors/ComponentInspector.h"

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
		std::unordered_map<std::type_index, std::unique_ptr<ComponentInspector>> m_ComponentInspectorRegistry;

		Tavern::EventListener<EntitySelectedEvent> m_EntitySelectedEvent;

		void OnEntitySelected(std::shared_ptr<EntitySelectedEvent> event);

		template <typename ComponentType, typename InspectorType>
		void RegisterComponentInspector()
		{
			m_ComponentInspectorRegistry[typeid(ComponentType)] = std::make_unique<InspectorType>();
		}
	};
}