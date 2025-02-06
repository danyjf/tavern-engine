#include <filesystem>
#include <fstream>

#include <Tavern/Core/Engine.h>
#include <Tavern/Core/Log.h>
#include <Tavern/Core/Core.h>
#include <Tavern/Scene/Entity.h>
#include <Tavern/Components/ScriptComponent.h>
#include <Tavern/Components/MeshComponent.h>
#include <Tavern/Components/LightComponent.h>

#include "Taverner/Editor.h"

using namespace Tavern;

int main()
{
	// Setup Tavern Engine
	Engine engine;
	engine.GetTimeManager().SetTimeScale(0.0f);
	Taverner::Editor editor(engine);

	while (engine.IsRunning())
	{
		engine.HandleEvents();
		engine.Update();

		editor.GetGameWindow().GetGameFramebuffer().Bind();
		engine.Render();
		editor.GetGameWindow().GetGameFramebuffer().Unbind();

		editor.Render();
	}

	return 0;
}
