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

		template <typename EntityClass>
		Entity* CreateEntity()
		{
			m_Entities.push_back(new EntityClass());
			return m_Entities.back();
		}

		void OnWindowCloseEvent(const std::shared_ptr<Event>& event);

	private:
		bool m_IsRunning = true;

		std::vector<Entity*> m_Entities;
	};
}
