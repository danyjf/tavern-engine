set(SOURCES
	vendor/Glad/src/glad.c
    vendor/stb/stb.cpp
)
set(SOURCES_TAVERN
)
set(SOURCES_TAVERN_COMPONENTS
    src/Tavern/Components/Component.h
    src/Tavern/Components/Component.cpp
    src/Tavern/Components/ScriptComponent.h
    src/Tavern/Components/ScriptComponent.cpp
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
    src/Tavern/Scene/ScriptRegistry.h
    src/Tavern/Scene/ScriptRegistry.cpp
)
set(SOURCES_TAVERN_UI
    src/Tavern/UI/UIManager.h
    src/Tavern/UI/UIManager.cpp
    src/Tavern/UI/UIElement.h
    src/Tavern/UI/UIElement.cpp
    src/Tavern/UI/Panel.h
    src/Tavern/UI/Panel.cpp
    src/Tavern/UI/MenuBar.h
    src/Tavern/UI/MenuBar.cpp
    src/Tavern/UI/Image.h
    src/Tavern/UI/Image.cpp
    src/Tavern/UI/Button.h
    src/Tavern/UI/Button.cpp
    src/Tavern/UI/FileDialog.h
    src/Tavern/UI/FileDialog.cpp
)
set(VENDOR_IMGUI
    vendor/imgui/imconfig.h
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui.h
    vendor/imgui/imgui_demo.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_internal.h
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/imstb_rectpack.h
    vendor/imgui/imstb_textedit.h
    vendor/imgui/imstb_truetype.h

    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/backends/imgui_impl_glfw.h
    vendor/imgui/backends/imgui_impl_opengl3.cpp
    vendor/imgui/backends/imgui_impl_opengl3.h

    vendor/imgui/misc/debuggers/imgui.natvis
    vendor/imgui/misc/debuggers/imgui.natstepfilter

    vendor/imgui/misc/cpp/imgui_stdlib.cpp
    vendor/imgui/misc/cpp/imgui_stdlib.h
)
set(VENDOR_IMGUIFILEDIALOG
    vendor/ImGuiFileDialog/ImGuiFileDialog.cpp
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
source_group(src/Tavern/UI FILES ${SOURCES_TAVERN_UI})
source_group(vendor/imgui FILES ${VENDOR_IMGUI})
source_group(vendor/ImGuiFileDialog FILES ${VENDOR_IMGUIFILEDIALOG})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Tavern)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Tavern)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Tavern)

set(BUILD_SHARED_LIBS ON)
add_subdirectory(vendor/GLFW)
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(vendor/glm)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(vendor/nlohmann_json)

set(ASSIMP_WARNINGS_AS_ERRORS OFF)
add_subdirectory(vendor/assimp)

add_library(Tavern SHARED 
    ${SOURCES} 
    ${SOURCES_TAVERN} 
    ${SOURCES_TAVERN_COMPONENTS}
    ${SOURCES_TAVERN_CORE}
    ${SOURCES_TAVERN_EVENTS}
    ${SOURCES_TAVERN_INPUT}
    ${SOURCES_TAVERN_RENDERER}
    ${SOURCES_TAVERN_RESOURCES}
    ${SOURCES_TAVERN_SCENE}
    ${SOURCES_TAVERN_UI}
    ${VENDOR_IMGUI}
    ${VENDOR_IMGUIFILEDIALOG}
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
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/imgui
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/imgui/backends
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/ImGuiFileDialog
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

add_custom_command(TARGET Tavern POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIRECTORY}/EngineTestProject
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Tavern> ${OUTPUT_DIRECTORY}/EngineTestProject
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:glfw> ${OUTPUT_DIRECTORY}/EngineTestProject
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${OUTPUT_DIRECTORY}/EngineTestProject/BuiltInAssets
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIRECTORY}/Taverner
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Tavern> ${OUTPUT_DIRECTORY}/Taverner
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_LINKER_FILE:Tavern> ${OUTPUT_DIRECTORY}/Taverner
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:glfw> ${OUTPUT_DIRECTORY}/Taverner
)
