#pragma once

#ifdef TAVERN_PLATFORM_WINDOWS
	#ifdef TAVERN_BUILD_DLL
		#define TAVERN_API __declspec(dllexport)
		//#define TAVERN_API
	#else
		#define TAVERN_API __declspec(dllimport)
		//#define TAVERN_API
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

#define REGISTER_ENTITY(TYPE)																 \
	static bool TYPE##Registered = []() {													 \
		UserDefinedEntityRegistry::Get().Register(#TYPE, []() -> Entity* {					 \
			auto entity = UserDefinedEntityRegistry::Get().GetScene()->CreateEntity<TYPE>(); \
			entity->SetTypeName(#TYPE);														 \
			return entity;																	 \
		});																					 \
		return true;																		 \
	}();
