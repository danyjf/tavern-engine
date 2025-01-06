set(SOURCES_TAVERNER
	src/Taverner/main.cpp
    src/Taverner/Editor.h
    src/Taverner/Editor.cpp
)

source_group(src/Taverner FILES ${SOURCES_TAVERNER})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Taverner)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Taverner)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Taverner)

add_executable(Taverner 
    ${SOURCES_TAVERNER}
    ${SOURCES_TAVERNER_WINDOWS}
    CMakeLists.txt
)

target_include_directories(Taverner PRIVATE 
	${CMAKE_SOURCE_DIR}/Tavern/src
	${CMAKE_SOURCE_DIR}/Tavern/vendor/spdlog/include	
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/Glad/include
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/imgui
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/imgui/backends
    ${CMAKE_SOURCE_DIR}/Taverner/src
)

if(WIN32)
    add_compile_definitions(TAVERN_PLATFORM_WINDOWS) 
endif()

target_link_libraries(Taverner PRIVATE
    Tavern
    glfw
    glm::glm
    nlohmann_json::nlohmann_json
    assimp
)

set_target_properties(Taverner PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${OUTPUT_DIRECTORY}/Taverner"
)
