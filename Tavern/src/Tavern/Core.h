#pragma once

#ifdef TAVERN_PLATFORM_WINDOWS
	#ifdef TAVERN_BUILD_DLL
		#define TAVERN_API __declspec(dllexport)
	#else
		#define TAVERN_API __declspec(dllimport)
	#endif
#endif

#ifdef TAVERN_ENABLE_ASSERTS
	#define TAVERN_ENGINE_ASSERT(x, ...)                                   \
		{                                                                  \
			if (!(x))                                                      \
			{                                                              \
				TAVERN_ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
				__debugbreak();                                            \
			}                                                              \
		}
	#define TAVERN_ASSERT(x, ...)                                   \
		{                                                           \
			if (!(x))                                               \
			{                                                       \
				TAVERN_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
				__debugbreak();                                     \
			}                                                       \
		}
#else
	#define TAVERN_ENGINE_ASSERT(x, ...)
	#define TAVERN_ASSERT(x, ...)
#endif
