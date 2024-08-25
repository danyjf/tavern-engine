#pragma once

#ifdef TAVERN_PLATFORM_WINDOWS
	#ifdef TAVERN_BUILD_DLL
		#define TAVERN_API __declspec(dllexport)
	#else
		#define TAVERN_API __declspec(dllimport)
	#endif
#endif

