#pragma once

#include <imgui.h>

#include <Tavern/Core/Engine.h>

namespace Taverner
{
	class InspectorWindow
	{
	public:
		InspectorWindow(Tavern::Engine& engine);

		void Render();

	private:
		Tavern::Engine& m_Engine;
	};
}