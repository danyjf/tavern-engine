#include "Tavern/Renderer/RenderManager.h"
#include "Tavern/Renderer/Window.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Core/Log.h"

namespace Tavern
{
	RenderManager& RenderManager::Get()
	{
		static RenderManager s_RenderManager;
		return s_RenderManager;
	}

	void RenderManager::Init()
	{
		m_Window = std::unique_ptr<Window>(new Window());
		m_Window->Init(WindowSettings("My Window", 800, 600));

		EventManager::Get().AddListener(EventType::WindowResize, std::bind(&RenderManager::OnWindowResizeEvent, this, std::placeholders::_1));

		m_Shader = std::unique_ptr<Shader>(new Shader(
			"./Shaders/Shader.vert",
			"./Shaders/Shader.frag"));
	}

	void RenderManager::Shutdown()
	{
	}

	void RenderManager::OnWindowResizeEvent(const std::shared_ptr<Event>& event)
	{
		std::shared_ptr<WindowResizeEvent> windowResizeEvent = std::dynamic_pointer_cast<WindowResizeEvent>(event);
		glViewport(0, 0, windowResizeEvent->width, windowResizeEvent->height);

		TAVERN_ENGINE_TRACE("Window Resize Event: ({0}, {1})", windowResizeEvent->width, windowResizeEvent->height);
	}
}
