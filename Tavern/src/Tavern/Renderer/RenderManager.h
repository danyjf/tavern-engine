#pragma once

#include <memory>
#include <unordered_set>

#include "Tavern/Components/CameraComponent.h"
#include "Tavern/Components/RenderComponent.h"
#include "Tavern/Core/Core.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Events/EventListener.h"
#include "Tavern/Renderer/Window.h"
#include "Tavern/Resources/ResourceManager.h"

namespace Tavern
{
	class Event;
	class EventManager;
	class LightComponent;
	class ShaderResource;
	class MaterialResource;

	// TODO: Maybe create a RenderGraph data structure to better organize the render order
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
		void AddLightComponent(LightComponent* lightComponent);
		void RemoveLightComponent(LightComponent* lightComponent);

		void Render();

		void OnWindowResizeEvent(const std::shared_ptr<WindowResizeEvent> event);

	private:
		EventManager& m_EventManager;
		EventListener<WindowResizeEvent> m_WindowResizeListener;
		std::unique_ptr<Window> m_Window;
		CameraComponent* m_Camera = nullptr;

		// Map associating shader with set of materials
		std::unordered_map<ShaderResource*, std::unordered_set<MaterialResource*>> m_Materials;
		// Map associating material with set of render components
		std::unordered_map<MaterialResource*, std::unordered_set<RenderComponent*>> m_RenderComponents;
		std::unordered_set<LightComponent*> m_LightComponents;
	};
}
