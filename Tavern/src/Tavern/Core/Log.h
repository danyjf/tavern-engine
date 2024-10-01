#pragma once

#include <spdlog/spdlog.h>

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class TAVERN_API Log
	{
	public:
		Log(const Log&) = delete;
		Log& operator=(const Log&) = delete;

		static Log& Get();

		inline std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
		inline std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		Log();

		std::shared_ptr<spdlog::logger> s_EngineLogger;
		std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define TAVERN_ENGINE_TRACE(...) ::Tavern::Log::Get().GetEngineLogger()->trace(__VA_ARGS__)
#define TAVERN_ENGINE_INFO(...) ::Tavern::Log::Get().GetEngineLogger()->info(__VA_ARGS__)
#define TAVERN_ENGINE_WARN(...) ::Tavern::Log::Get().GetEngineLogger()->warn(__VA_ARGS__)
#define TAVERN_ENGINE_ERROR(...) ::Tavern::Log::Get().GetEngineLogger()->error(__VA_ARGS__)
#define TAVERN_ENGINE_CRITICAL(...) ::Tavern::Log::Get().GetEngineLogger()->critical(__VA_ARGS__)

// Client log macros
#define TAVERN_TRACE(...) ::Tavern::Log::Get().GetClientLogger()->trace(__VA_ARGS__)
#define TAVERN_INFO(...) ::Tavern::Log::Get().GetClientLogger()->info(__VA_ARGS__)
#define TAVERN_WARN(...) ::Tavern::Log::Get().GetClientLogger()->warn(__VA_ARGS__)
#define TAVERN_ERROR(...) ::Tavern::Log::Get().GetClientLogger()->error(__VA_ARGS__)
#define TAVERN_CRITICAL(...) ::Tavern::Log::Get().GetClientLogger()->critical(__VA_ARGS__)
