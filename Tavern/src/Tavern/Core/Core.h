#pragma once

#ifdef TAVERN_PLATFORM_WINDOWS
	#ifdef TAVERN_BUILD_DLL
		#define TAVERN_API __declspec(dllexport)
	#else
		#define TAVERN_API __declspec(dllimport)
	#endif
#else
	#define TAVERN_API
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

#define REGISTER_SCRIPT(TYPE)																		\
	static bool TYPE##Registered = []() {															\
		ScriptRegistry::Get().Register(#TYPE, [](Entity* entity) -> ScriptComponent* {	\
			auto script = entity->CreateComponentOfType<TYPE>();									\
			script->SetTypeName(#TYPE);																\
			return script;																			\
		});																							\
		return true;																				\
	}();
