cmake_minimum_required(VERSION 3.30)

project(EditorTestProject)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SOURCES
../Cube.h
../Cube.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
../../Tavern/src
../../Tavern/vendor/spdlog/include
../../Tavern/vendor/Glad/include
)
target_link_libraries(${PROJECT_NAME} PRIVATE
C:/Dev/tavern-engine/bin/Debug-Windows-x64/Tavern/Tavernd.lib
)

