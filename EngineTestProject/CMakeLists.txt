set(SOURCES
	src/main.cpp
	src/Backpack.cpp
	src/Backpack.h
    src/Cube.cpp
	src/Cube.h
    src/Light.cpp
	src/Light.h
	src/Player.cpp
	src/Player.h
	src/Ground.cpp
	src/Ground.h
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/EngineTestProject)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/EngineTestProject)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/EngineTestProject)

add_executable(EngineTestProject 
    ${SOURCES}
    CMakeLists.txt
)

source_group(src FILES ${SOURCES})

target_include_directories(EngineTestProject PRIVATE 
	${CMAKE_SOURCE_DIR}/Tavern/src
	${CMAKE_SOURCE_DIR}/Tavern/vendor/spdlog/include	
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/Glad/include
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/imgui
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/imgui/backends
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/ImGuiFileDialog
)

target_compile_definitions(EngineTestProject PRIVATE
	$<$<CONFIG:Debug>:TAVERN_DEBUG>
	$<$<CONFIG:Release>:TAVERN_RELEASE>
)

if(WIN32)
    add_compile_definitions(TAVERN_PLATFORM_WINDOWS) 
endif()

if(UNIX)
    add_compile_definitions(TAVERN_PLATFORM_UNIX) 
endif()

target_link_libraries(EngineTestProject PRIVATE
    Tavern
    glfw
    glm::glm
    nlohmann_json::nlohmann_json
    assimp
)

set_target_properties(EngineTestProject PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${OUTPUT_DIRECTORY}/EngineTestProject"
)

add_custom_command(TARGET EngineTestProject POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/Assets
	COMMAND ${CMAKE_COMMAND} -E rm -rf ${OUTPUT_DIRECTORY}/EngineTestProject/Assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${OUTPUT_DIRECTORY}/EngineTestProject/Assets
)
