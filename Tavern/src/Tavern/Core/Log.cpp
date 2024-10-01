#include <spdlog/sinks/stdout_color_sinks.h>

#include "Tavern/Core/Log.h"

namespace Tavern
{
	Log::Log()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_EngineLogger = spdlog::stdout_color_mt("TAVERN");
		s_EngineLogger->set_level(spdlog::level::level_enum::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::level_enum::trace);
	}

	Log& Log::Get()
	{
		static Log log;
		return log;
	}
}
