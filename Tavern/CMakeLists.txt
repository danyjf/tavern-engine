set(SOURCES
    src/Tavern.h
	vendor/Glad/src/glad.c
    vendor/stb/stb.cpp
)
set(SOURCES_TAVERN
    src/Tavern/Entity.h
    src/Tavern/Entity.cpp
)
set(SOURCES_TAVERN_COMPONENTS
    src/Tavern/Components/Component.h
    src/Tavern/Components/Component.cpp
    src/Tavern/Components/CameraComponent.h
    src/Tavern/Components/CameraComponent.cpp
    src/Tavern/Components/TransformComponent.h
    src/Tavern/Components/TransformComponent.cpp
    src/Tavern/Components/RenderComponent.h
    src/Tavern/Components/RenderComponent.cpp
    src/Tavern/Components/MeshRenderComponent.h
    src/Tavern/Components/MeshRenderComponent.cpp
)
set(SOURCES_TAVERN_CORE
    src/Tavern/Core/Core.h
    src/Tavern/Core/Engine.h
    src/Tavern/Core/Engine.cpp
    src/Tavern/Core/Log.h
    src/Tavern/Core/Log.cpp
    src/Tavern/Core/Time.h
    src/Tavern/Core/Time.cpp
)
set(SOURCES_TAVERN_EVENTS
	src/Tavern/Events/EventManager.h
	src/Tavern/Events/EventManager.cpp
	src/Tavern/Events/Event.h
	src/Tavern/Events/ApplicationEvent.h
	src/Tavern/Events/KeyEvent.h
    src/Tavern/Events/EventListenerInterface.h
    src/Tavern/Events/EventListener.h
)
set(SOURCES_TAVERN_INPUT
    src/Tavern/Input/InputManager.h
    src/Tavern/Input/InputManager.cpp
    src/Tavern/Input/KeyCodes.h
    src/Tavern/Input/MouseCodes.h
)
set(SOURCES_TAVERN_RENDERER
    src/Tavern/Renderer/RenderManager.h
    src/Tavern/Renderer/RenderManager.cpp
    src/Tavern/Renderer/Window.h
	src/Tavern/Renderer/Window.cpp
    src/Tavern/Renderer/Cursor.h
    src/Tavern/Renderer/Cursor.cpp
)
set(SOURCES_TAVERN_RESOURCES
    src/Tavern/Resources/ResourceManager.h
    src/Tavern/Resources/ResourceManager.cpp
    src/Tavern/Resources/Resource.h
    src/Tavern/Resources/Resource.cpp
    src/Tavern/Resources/ShaderResource.h
    src/Tavern/Resources/ShaderResource.cpp
    src/Tavern/Resources/TextureResource.h
    src/Tavern/Resources/TextureResource.cpp
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Tavern)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Tavern)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Tavern)

add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/glm)

add_library(Tavern SHARED 
    ${SOURCES} 
    ${SOURCES_TAVERN} 
    ${SOURCES_TAVERN_COMPONENTS}
    ${SOURCES_TAVERN_CORE}
    ${SOURCES_TAVERN_EVENTS}
    ${SOURCES_TAVERN_INPUT}
    ${SOURCES_TAVERN_RENDERER}
    ${SOURCES_TAVERN_RESOURCES}
)

source_group(src FILES ${SOURCES})
source_group(src/Tavern FILES ${SOURCES_TAVERN})
source_group(src/Tavern/Components FILES ${SOURCES_TAVERN_COMPONENTS})
source_group(src/Tavern/Core FILES ${SOURCES_TAVERN_CORE})
source_group(src/Tavern/Events FILES ${SOURCES_TAVERN_EVENTS})
source_group(src/Tavern/Input FILES ${SOURCES_TAVERN_INPUT})
source_group(src/Tavern/Renderer FILES ${SOURCES_TAVERN_RENDERER})
source_group(src/Tavern/Resources FILES ${SOURCES_TAVERN_RESOURCES})

target_include_directories(Tavern PRIVATE 
    ${CMAKE_SOURCE_DIR}/Tavern/src
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/Glad/include
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/stb/include
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
	$<$<COMPILE_LANGUAGE:CXX>:<algorithm$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<fstream$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<functional$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<iostream$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<memory$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<queue$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<sstream$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<string$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<unordered_map$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<unordered_set$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<utility$<ANGLE-R>>
	$<$<COMPILE_LANGUAGE:CXX>:<vector$<ANGLE-R>>

	# Include only for windows
	$<$<COMPILE_LANGUAGE:CXX>:$<$<PLATFORM_ID:Windows>:<Windows.h$<ANGLE-R>>>
)

target_link_libraries(Tavern PRIVATE 
    glfw
    glm::glm
)

add_custom_target(CopyEngineFiles ALL
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Tavern> ${OUTPUT_DIRECTORY}/Sandbox
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/src/Tavern/Renderer/Shaders ${OUTPUT_DIRECTORY}/Sandbox/Shaders
)
add_dependencies(CopyEngineFiles Tavern Sandbox)
