set(SOURCES_TAVERNER
    src/Taverner/main.cpp
)
set(SOURCES_TAVERNER_CORE
    src/Taverner/Core/ProjectConfig.h
    src/Taverner/Core/ProjectConfig.cpp
    src/Taverner/Core/EditorCamera.h
    src/Taverner/Core/EditorCamera.cpp
    src/Taverner/Core/Editor.h
    src/Taverner/Core/Editor.cpp
)
set(SOURCES_TAVERNER_WINDOWS
    src/Taverner/Windows/FileSystemWindow.h
    src/Taverner/Windows/FileSystemWindow.cpp
    src/Taverner/Windows/GameWindow.h
    src/Taverner/Windows/GameWindow.cpp
    src/Taverner/Windows/SceneWindow.h
    src/Taverner/Windows/SceneWindow.cpp
    src/Taverner/Windows/InspectorWindow.h
    src/Taverner/Windows/InspectorWindow.cpp
)
set(SOURCES_TAVERNER_EVENTS
    src/Taverner/Events/EditorEvents.h
    src/Taverner/Events/EditorEvents.cpp
)
set(SOURCES_TAVERNER_COMPONENTINSPECTORS
    src/Taverner/ComponentInspectors/ComponentInspector.h
    src/Taverner/ComponentInspectors/TransformComponentInspector.h
    src/Taverner/ComponentInspectors/TransformComponentInspector.cpp
    src/Taverner/ComponentInspectors/CameraComponentInspector.h
    src/Taverner/ComponentInspectors/CameraComponentInspector.cpp
    src/Taverner/ComponentInspectors/LightComponentInspector.h
    src/Taverner/ComponentInspectors/LightComponentInspector.cpp
    src/Taverner/ComponentInspectors/MeshComponentInspector.h
    src/Taverner/ComponentInspectors/MeshComponentInspector.cpp
    src/Taverner/ComponentInspectors/ScriptComponentInspector.h
    src/Taverner/ComponentInspectors/ScriptComponentInspector.cpp
)
set(VENDOR_IMGUI_BINDINGS
    vendor/imgui/bindings/imgui_impl_glfw.cpp
    vendor/imgui/bindings/imgui_impl_glfw.h
    vendor/imgui/bindings/imgui_impl_opengl3.cpp
    vendor/imgui/bindings/imgui_impl_opengl3.h
    vendor/imgui/bindings/imgui_impl_opengl3_loader.h
)
set(VENDOR_IMGUIFILEDIALOG
    vendor/ImGuiFileDialog/ImGuiFileDialog.cpp
)

source_group(src/Taverner FILES ${SOURCES_TAVERNER})
source_group(src/Taverner/Core FILES ${SOURCES_TAVERNER_CORE})
source_group(src/Taverner/Windows FILES ${SOURCES_TAVERNER_WINDOWS})
source_group(src/Taverner/Events FILES ${SOURCES_TAVERNER_EVENTS})
source_group(src/Taverner/ComponentInspectors FILES ${SOURCES_TAVERNER_COMPONENTINSPECTORS})
source_group(vendor/imgui/bindings FILES ${VENDOR_IMGUI_BINDINGS})
source_group(vendor/ImGuiFileDialog FILES ${VENDOR_IMGUIFILEDIALOG})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Taverner)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Taverner)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Taverner)

add_executable(Taverner 
    ${SOURCES_TAVERNER}
    ${SOURCES_TAVERNER_CORE}
    ${SOURCES_TAVERNER_WINDOWS}
    ${SOURCES_TAVERNER_EVENTS}
    ${SOURCES_TAVERNER_COMPONENTINSPECTORS}
    ${VENDOR_IMGUI_BINDINGS}
    ${VENDOR_IMGUIFILEDIALOG}
    CMakeLists.txt
)

target_include_directories(Taverner PRIVATE 
	${CMAKE_SOURCE_DIR}/Tavern/src
    ${CMAKE_SOURCE_DIR}/Taverner/vendor/imgui/bindings
    ${CMAKE_SOURCE_DIR}/Taverner/vendor/ImGuiFileDialog
    ${CMAKE_SOURCE_DIR}/Taverner/src
)

if(WIN32)
    add_compile_definitions(TAVERN_PLATFORM_WINDOWS) 
endif()

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(assimp REQUIRED)
find_package(spdlog REQUIRED)
find_package(glad REQUIRED)
find_package(imgui REQUIRED)

target_link_libraries(Taverner PRIVATE
    Tavern
    glfw
    glm::glm
    nlohmann_json::nlohmann_json
    assimp::assimp
    spdlog::spdlog
    glad::glad
    imgui::imgui
)

set_target_properties(Taverner PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${OUTPUT_DIRECTORY}/Taverner"
)
