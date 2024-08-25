cmake_minimum_required(VERSION 3.30)

# Set the C++ version to use
set(CMAKE_CXX_STANDARD 17)

# Suppress generation of ZERO_CHECK
set(CMAKE_SUPPRESS_REGENERATION true)

set(CMAKE_CONFIGURATION_TYPES
	Debug
	Release
)

project(Tavern)

# Base output directory used for the projects
set(OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-x64)

add_subdirectory(Tavern)
add_subdirectory(Sandbox)

# Set the Sandbox project as the startup project on visual studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)
