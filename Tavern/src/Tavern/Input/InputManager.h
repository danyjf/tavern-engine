#pragma once

#include <glm/fwd.hpp>

#include "Tavern/Core/Core.h"
#include "Tavern/Input/MouseCodes.h"
#include "Tavern/Input/KeyCodes.h"
#include "Tavern/Renderer/Window.h"

namespace Tavern
{
	class TAVERN_API InputManager
	{
	public:
		InputManager();
		~InputManager();
		InputManager(InputManager& copy) = delete;
		void operator=(const InputManager& copy) = delete;

		void Init();
		void Shutdown();

		bool IsKeyPressed(const Key key);
		bool IsMouseButtonPressed(const Mouse button);

		glm::vec2 GetMousePosition();

	private:
		Window* m_Window;
	};

	extern TAVERN_API InputManager gInputManager;
}
