cmake_minimum_required(VERSION 4.1.1)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(Tavern)

# Set the C++ version to use
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_SCAN_FOR_MODULES 0)

# Export a compile_comands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Suppress generation of ZERO_CHECK
set(CMAKE_SUPPRESS_REGENERATION true)

# Set the available configuration types
set(CMAKE_CONFIGURATION_TYPES
	Debug
	Release
)

# Base output directory used for the projects
set(OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-x64)

add_subdirectory(Tavern)
add_subdirectory(EngineTestProject)
add_subdirectory(Taverner)

# Set the EngineTestProject project as the startup project on visual studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT EngineTestProject)
