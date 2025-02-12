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

source_group(src/Taverner FILES ${SOURCES_TAVERNER})
source_group(src/Taverner/Core FILES ${SOURCES_TAVERNER_CORE})
source_group(src/Taverner/Windows FILES ${SOURCES_TAVERNER_WINDOWS})
source_group(src/Taverner/Events FILES ${SOURCES_TAVERNER_EVENTS})
source_group(vendor/imgui FILES ${VENDOR_IMGUI})
source_group(vendor/ImGuiFileDialog FILES ${VENDOR_IMGUIFILEDIALOG})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Taverner)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Taverner)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Taverner)

add_executable(Taverner 
    ${SOURCES_TAVERNER}
    ${SOURCES_TAVERNER_CORE}
    ${SOURCES_TAVERNER_WINDOWS}
    ${SOURCES_TAVERNER_EVENTS}
    ${VENDOR_IMGUI}
    ${VENDOR_IMGUIFILEDIALOG}
    CMakeLists.txt
)

target_include_directories(Taverner PRIVATE 
	${CMAKE_SOURCE_DIR}/Tavern/src
	${CMAKE_SOURCE_DIR}/Tavern/vendor/spdlog/include	
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/Glad/include
    ${CMAKE_SOURCE_DIR}/Taverner/vendor/imgui
    ${CMAKE_SOURCE_DIR}/Taverner/vendor/imgui/backends
    ${CMAKE_SOURCE_DIR}/Taverner/vendor/ImGuiFileDialog
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
