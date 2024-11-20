cmake_minimum_required(VERSION 3.30)

project(EditorTestProject)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY .taverner/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY .taverner/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY .taverner/)

set(SOURCES
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
../Tavern/src
../Tavern/vendor/spdlog/include
../Tavern/vendor/Glad/include
)

