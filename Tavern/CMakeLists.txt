set(SOURCES
    src/Tavern.h
	vendor/Glad/src/glad.c
)
set(SOURCES_TAVERN
	src/Tavern/Core.h
	src/Tavern/Engine.h
	src/Tavern/Engine.cpp
	src/Tavern/Log.h
	src/Tavern/Log.cpp
	src/Tavern/Window.h
	src/Tavern/Window.cpp
)
set(SOURCES_TAVERN_EVENTS
	src/Tavern/Events/Event.h
	src/Tavern/Events/ApplicationEvent.h
	src/Tavern/Events/EventManager.h
	src/Tavern/Events/EventManager.cpp
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Tavern)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Tavern)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Tavern)

add_subdirectory(vendor/GLFW)

add_library(Tavern SHARED ${SOURCES} ${SOURCES_TAVERN} ${SOURCES_TAVERN_EVENTS})

source_group(src FILES ${SOURCES})
source_group(src/Tavern FILES ${SOURCES_TAVERN})
source_group(src/Tavern/Events FILES ${SOURCES_TAVERN_EVENTS})

target_include_directories(Tavern PRIVATE 
    ${CMAKE_SOURCE_DIR}/Tavern/src
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/Glad/include
)

target_compile_definitions(Tavern PRIVATE
	TAVERN_BUILD_DLL
	$<$<CONFIG:Debug>:TAVERN_DEBUG>
	$<$<CONFIG:Release>:TAVERN_RELEASE>
)

if(WIN32)
    add_compile_definitions(TAVERN_PLATFORM_WINDOWS) 
endif()

target_precompile_headers(Tavern PRIVATE 
	$<$<COMPILE_LANGUAGE:CXX>:<iostream$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<iostream$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<memory$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<utility$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<algorithm$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<functional$<ANGLE-R>>

	$<$<COMPILE_LANGUAGE:CXX>:<string$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<sstream$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<vector$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<unordered_map$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<unordered_set$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<queue$<ANGLE-R>>

	# Include only for windows
	$<$<COMPILE_LANGUAGE:CXX>:$<$<PLATFORM_ID:Windows>:<Windows.h$<ANGLE-R>>>
)

target_link_libraries(Tavern glfw)

# Copy the Tavern dll into the Sandbox project folder
add_custom_command(TARGET Tavern 
    POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIRECTORY}/Sandbox
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Tavern> ${OUTPUT_DIRECTORY}/Sandbox
)
