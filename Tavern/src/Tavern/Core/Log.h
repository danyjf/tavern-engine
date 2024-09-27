#pragma once

#include <spdlog/spdlog.h>

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class TAVERN_API Log
	{
	public:
		Log() = delete;

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define TAVERN_ENGINE_TRACE(...) ::Tavern::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define TAVERN_ENGINE_INFO(...) ::Tavern::Log::GetEngineLogger()->info(__VA_ARGS__)
#define TAVERN_ENGINE_WARN(...) ::Tavern::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define TAVERN_ENGINE_ERROR(...) ::Tavern::Log::GetEngineLogger()->error(__VA_ARGS__)
#define TAVERN_ENGINE_CRITICAL(...) ::Tavern::Log::GetEngineLogger()->critical(__VA_ARGS__)

// Client log macros
#define TAVERN_TRACE(...) ::Tavern::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TAVERN_INFO(...) ::Tavern::Log::GetClientLogger()->info(__VA_ARGS__)
#define TAVERN_WARN(...) ::Tavern::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TAVERN_ERROR(...) ::Tavern::Log::GetClientLogger()->error(__VA_ARGS__)
#define TAVERN_CRITICAL(...) ::Tavern::Log::GetClientLogger()->critical(__VA_ARGS__)
