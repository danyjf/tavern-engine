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

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(assimp REQUIRED)
find_package(spdlog REQUIRED)
find_package(glad REQUIRED)

target_link_libraries(EngineTestProject PRIVATE
    Tavern
    glfw
    glm::glm
    nlohmann_json::nlohmann_json
    assimp::assimp
    spdlog::spdlog
    glad::glad
)

set_target_properties(EngineTestProject PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${OUTPUT_DIRECTORY}/EngineTestProject"
)

add_custom_command(TARGET EngineTestProject POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/Assets
	COMMAND ${CMAKE_COMMAND} -E rm -rf ${OUTPUT_DIRECTORY}/EngineTestProject/Assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${OUTPUT_DIRECTORY}/EngineTestProject/Assets
)
