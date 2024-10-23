set(SOURCES
	src/SandboxApp.cpp
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Sandbox)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Sandbox)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Sandbox)

add_executable(Sandbox ${SOURCES})

source_group(src FILES ${SOURCES})

target_include_directories(Sandbox PRIVATE 
	${CMAKE_SOURCE_DIR}/Tavern/src
	${CMAKE_SOURCE_DIR}/Tavern/vendor/spdlog/include	
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/Glad/include
)

target_compile_definitions(Sandbox PRIVATE
	$<$<CONFIG:Debug>:TAVERN_DEBUG>
	$<$<CONFIG:Release>:TAVERN_RELEASE>
)

if(WIN32)
    add_compile_definitions(TAVERN_PLATFORM_WINDOWS) 
endif()

target_link_libraries(Sandbox PRIVATE
    Tavern
    glfw
    glm::glm
)

add_custom_command(TARGET Sandbox
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/Assets
	COMMAND ${CMAKE_COMMAND} -E rm -rf ${OUTPUT_DIRECTORY}/Sandbox/Assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${OUTPUT_DIRECTORY}/Sandbox/Assets
)
