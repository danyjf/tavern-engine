#include "Engine.h"
#include "Log.h"

namespace Tavern
{
	Engine::Engine()
	{
	}

	Engine::~Engine()
	{
	}

	void Engine::Run()
	{
		Init();

		while (true);
	}

	void Engine::Init()
	{
		Tavern::Log::Init();
		TAVERN_ENGINE_WARN("Initialized Engine Log!");
		TAVERN_INFO("Hello {:d}", 10);
	}
}

