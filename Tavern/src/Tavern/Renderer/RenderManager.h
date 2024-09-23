#pragma once

#include <memory>

#include "Tavern/Renderer/Camera.h"
#include "Tavern/Renderer/Shader.h"
#include "Tavern/Renderer/Window.h"
#include "Tavern/Events/Event.h"

namespace Tavern
{
	class RenderManager
	{
	public:
		RenderManager(RenderManager& copy) = delete;
		void operator=(const RenderManager& copy) = delete;

		static RenderManager& Get();

		void Init();
		void Shutdown();

		Window* GetWindow() const { return m_Window.get(); }
		Shader* GetShader() const { return m_Shader.get(); }
		Camera* GetCamera() const { return m_Camera.get(); }

		void OnWindowResizeEvent(const std::shared_ptr<Event>& event);

	private:
		RenderManager() {};
		~RenderManager() {};

		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Camera> m_Camera;
	};
}
