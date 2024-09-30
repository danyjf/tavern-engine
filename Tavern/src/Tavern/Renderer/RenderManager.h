#pragma once

#include <memory>

#include "Tavern/Components/CameraComponent.h"
#include "Tavern/Components/MeshComponent.h"
#include "Tavern/Core/Core.h"
#include "Tavern/Renderer/Window.h"
#include "Tavern/Renderer/Shader.h"

namespace Tavern
{
	class Event;

	class TAVERN_API RenderManager
	{
	public:
		RenderManager();
		~RenderManager();
		RenderManager(RenderManager& copy) = delete;
		void operator=(const RenderManager& copy) = delete;

		void Init();
		void Shutdown();

		Window* GetWindow() const;
		Shader* GetShader() const;
		CameraComponent* GetActiveCamera() const;
		void SetActiveCamera(CameraComponent* camera);
		void AddMeshComponent(MeshComponent* meshComponent);

		void Render();

		void OnWindowResizeEvent(const std::shared_ptr<Event>& event);

	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Shader> m_Shader;
		CameraComponent* m_Camera;
		std::vector<MeshComponent*> m_MeshComponents;
	};

	extern TAVERN_API RenderManager gRenderManager;
}
