#pragma once

#include <memory>
#include <unordered_set>

#include "Tavern/Components/CameraComponent.h"
#include "Tavern/Components/RenderComponent.h"
#include "Tavern/Core/Core.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Renderer/Window.h"
#include "Tavern/Resources/ResourceManager.h"

namespace Tavern
{
	class Event;
	class EventManager;

	class TAVERN_API RenderManager
	{
	public:
		RenderManager(EventManager& eventManager, ResourceManager& resourceManager);
		~RenderManager();
		RenderManager(RenderManager& copy) = delete;
		RenderManager& operator=(const RenderManager& copy) = delete;

		Window* GetWindow() const;
		CameraComponent* GetActiveCamera() const;
		void SetActiveCamera(CameraComponent* camera);
		void AddRenderComponent(RenderComponent* renderComponent);
		void RemoveRenderComponent(RenderComponent* renderComponent);

		void Render();

		void OnWindowResizeEvent(const std::shared_ptr<WindowResizeEvent>& event);

	private:
		EventManager& m_EventManager;
		EventListener<WindowResizeEvent> m_WindowResizeListener;
		std::unique_ptr<Window> m_Window;
		CameraComponent* m_Camera = nullptr;
		std::unordered_set<RenderComponent*> m_RenderComponents;
	};
}
