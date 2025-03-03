#pragma once

#include <imgui.h>

#include <Tavern/Scene/Scene.h>
#include <Tavern/Events/EventListener.h>
#include <Tavern/Events/EventManager.h>

#include "Taverner/Events/EditorEvents.h"

namespace Taverner
{
	class SceneWindow
	{
	public:
		SceneWindow(Tavern::Scene& scene, Tavern::EventManager& eventManager);

		void Render();

	private:
		Tavern::Scene& m_Scene;
		Tavern::EventManager& m_EventManager;
		unsigned long m_SelectedEntityID = -1;

		Tavern::EventListener<ProjectLoadedEvent> m_ProjectLoadedEvent;

		void OnProjectLoaded(std::shared_ptr<ProjectLoadedEvent> event);
		void RenderEntityTree(Tavern::Entity* entity);
	};
}