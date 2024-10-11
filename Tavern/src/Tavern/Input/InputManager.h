#pragma once

#include <glm/fwd.hpp>

#include "Tavern/Core/Core.h"
#include "Tavern/Input/MouseCodes.h"
#include "Tavern/Input/KeyCodes.h"
#include "Tavern/Renderer/Window.h"

namespace Tavern
{
	class RenderManager;

	class TAVERN_API InputManager
	{
	public:
		InputManager(RenderManager& renderManager);
		~InputManager();
		InputManager(InputManager& copy) = delete;
		InputManager& operator=(const InputManager& copy) = delete;

		bool IsKeyPressed(const Key key);
		bool IsMouseButtonPressed(const Mouse button);

		glm::vec2 GetMousePosition();

	private:
		RenderManager& m_RenderManager;
		Window* m_Window = nullptr;
	};
}
