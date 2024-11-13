#include "Tavern/Core/Log.h"
#include "Tavern/Core/Engine.h"

int main()
{
	TAVERN_INFO("Launched Taverner Project");

	Tavern::Engine TavernEngine;

	while (TavernEngine.IsRunning())
	{
		TavernEngine.Update();
		TavernEngine.Render();

		// Render the editor
	}

	return 0;
}
