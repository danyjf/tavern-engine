#pragma once

#include <memory>
#include <vector>

#include "Tavern/Core/Core.h"
#include "Tavern/Events/Event.h"
#include "Tavern/Entity.h"

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

	private:
		bool m_IsRunning = true;

		std::vector<Entity> m_Entities;
	};
}
