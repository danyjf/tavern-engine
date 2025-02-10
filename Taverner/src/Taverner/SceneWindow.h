#pragma once

#include <imgui.h>

#include <Tavern/Core/Engine.h>

namespace Taverner
{
	class SceneWindow
	{
	public:
		SceneWindow(Tavern::Engine& engine);

		void Render();

	private:
		Tavern::Engine& m_Engine;
	};
}