#pragma once

#include <memory>

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Tavern
{
	class TAVERN_API Engine
	{
	public:
		Engine();
		~Engine();

		void Run();

		void OnWindowCloseEvent(const std::shared_ptr<Event>& event);
		void OnWindowResizeEvent(const std::shared_ptr<Event>& event);

	private:
		void Init();
		void GameLoop();
		void Shutdown();

		bool m_IsRunning = true;

		std::unique_ptr<Window> m_Window;
	};
}
