set(SOURCES
	src/Tavern.h
	src/Tavern/Core.h
	src/Tavern/Engine.cpp
	src/Tavern/Engine.h
	src/Tavern/Log.cpp
	src/Tavern/Log.h
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Tavern)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Tavern)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Tavern)

add_library(Tavern SHARED ${SOURCES})

target_include_directories(Tavern PRIVATE 
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/spdlog/include
)

target_compile_definitions(Tavern PRIVATE
	TAVERN_BUILD_DLL
	$<$<CONFIG:Debug>:TAVERN_DEBUG>
	$<$<CONFIG:Release>:TAVERN_RELEASE>
)

if(WIN32)
    add_compile_definitions(TAVERN_PLATFORM_WINDOWS) 
endif()
