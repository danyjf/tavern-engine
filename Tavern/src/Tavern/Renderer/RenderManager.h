#pragma once

#include <memory>

#include "Tavern/Components/Camera.h"
#include "Tavern/Core/Core.h"
#include "Tavern/Renderer/Window.h"
#include "Tavern/Renderer/Shader.h"

namespace Tavern
{
	class Event;

	class TAVERN_API RenderManager
	{
	public:
		RenderManager(RenderManager& copy) = delete;
		void operator=(const RenderManager& copy) = delete;

		static RenderManager& Get();

		void Init();
		void Shutdown();

		Window* GetWindow() const;
		Shader* GetShader() const;
		Camera* GetActiveCamera() const;
		void SetActiveCamera(Camera* camera);

		void OnWindowResizeEvent(const std::shared_ptr<Event>& event);

	private:
		RenderManager() {};
		~RenderManager() {};

		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Shader> m_Shader;
		Camera* m_Camera;
	};
}
