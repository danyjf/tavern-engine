#pragma once

#include <memory>
#include <vector>

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Entity.h"

namespace Tavern
{
	class TAVERN_API Engine
	{
	public:
		Engine();
		~Engine();

		void Init();
		void GameLoop();
		void Shutdown();

		void AddEntity(Entity& entity);

		void OnWindowCloseEvent(const std::shared_ptr<Event>& event);
		void OnWindowResizeEvent(const std::shared_ptr<Event>& event);

	private:
		bool m_IsRunning = true;

		std::unique_ptr<Window> m_Window;

		std::vector<Entity> m_Entities;
	};
}
