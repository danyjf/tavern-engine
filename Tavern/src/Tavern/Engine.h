#pragma once

#include "Core.h"

namespace Tavern
{
	class TAVERN_API Engine
	{
	public:
		Engine();
		~Engine();

		void Run();

	private:
		void Init();
	};
}

