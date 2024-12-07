set(SOURCES
	vendor/Glad/src/glad.c
    vendor/stb/stb.cpp
)
set(SOURCES_TAVERN
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
    src/Tavern/Components/MeshComponent.h
    src/Tavern/Components/MeshComponent.cpp
    src/Tavern/Components/LightComponent.h
    src/Tavern/Components/LightComponent.cpp
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
    src/Tavern/Renderer/Framebuffer.h
    src/Tavern/Renderer/Framebuffer.cpp
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
    src/Tavern/Resources/MaterialResource.h
    src/Tavern/Resources/MaterialResource.cpp
    src/Tavern/Resources/MeshResource.h
    src/Tavern/Resources/MeshResource.cpp
)
set(SOURCES_TAVERN_SCENE
    src/Tavern/Scene/Scene.h
    src/Tavern/Scene/Scene.cpp
    src/Tavern/Scene/Entity.h
    src/Tavern/Scene/Entity.cpp
    src/Tavern/Scene/UserDefinedEntityRegistry.h
    src/Tavern/Scene/UserDefinedEntityRegistry.cpp
)

source_group(src FILES ${SOURCES})
source_group(src/Tavern FILES ${SOURCES_TAVERN})
source_group(src/Tavern/Components FILES ${SOURCES_TAVERN_COMPONENTS})
source_group(src/Tavern/Core FILES ${SOURCES_TAVERN_CORE})
source_group(src/Tavern/Events FILES ${SOURCES_TAVERN_EVENTS})
source_group(src/Tavern/Input FILES ${SOURCES_TAVERN_INPUT})
source_group(src/Tavern/Renderer FILES ${SOURCES_TAVERN_RENDERER})
source_group(src/Tavern/Resources FILES ${SOURCES_TAVERN_RESOURCES})
source_group(src/Tavern/Scene FILES ${SOURCES_TAVERN_SCENE})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Tavern)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Tavern)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Tavern)

add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/glm)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(vendor/nlohmann_json)

set(ASSIMP_WARNINGS_AS_ERRORS OFF)
add_subdirectory(vendor/assimp)

add_library(Tavern STATIC 
    ${SOURCES} 
    ${SOURCES_TAVERN} 
    ${SOURCES_TAVERN_COMPONENTS}
    ${SOURCES_TAVERN_CORE}
    ${SOURCES_TAVERN_EVENTS}
    ${SOURCES_TAVERN_INPUT}
    ${SOURCES_TAVERN_RENDERER}
    ${SOURCES_TAVERN_RESOURCES}
    ${SOURCES_TAVERN_SCENE}
    CMakeLists.txt
)

target_link_libraries(Tavern PRIVATE 
    glfw
    glm::glm
    nlohmann_json::nlohmann_json
    assimp
)

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
	$<$<COMPILE_LANGUAGE:CXX>:<filesystem$<ANGLE-R>>
    $<$<COMPILE_LANGUAGE:CXX>:<glm/glm.hpp$<ANGLE-R>>
    $<$<COMPILE_LANGUAGE:CXX>:<glm/gtc/matrix_transform.hpp$<ANGLE-R>>

	# Include only for windows
	$<$<COMPILE_LANGUAGE:CXX>:$<$<PLATFORM_ID:Windows>:<Windows.h$<ANGLE-R>>>
)

add_custom_target(RunPostTavernBuild ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIRECTORY}/EngineTestProject
    #COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Tavern> ${OUTPUT_DIRECTORY}/EngineTestProject
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Tavern> ${OUTPUT_DIRECTORY}/Taverner
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:glfw> ${OUTPUT_DIRECTORY}/Taverner
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:glm::glm> ${OUTPUT_DIRECTORY}/Taverner
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:assimp> ${OUTPUT_DIRECTORY}/Taverner
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:zlibstatic> ${OUTPUT_DIRECTORY}/Taverner
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${OUTPUT_DIRECTORY}/EngineTestProject/BuiltInAssets
)

add_dependencies(RunPostTavernBuild Tavern)
