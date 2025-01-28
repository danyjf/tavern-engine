set(SOURCES_TAVERNER
	src/Taverner/main.cpp
    src/Taverner/Editor.h
    src/Taverner/Editor.cpp
    src/Taverner/ProjectConfig.h
    src/Taverner/ProjectConfig.cpp
)
set(VENDOR_IMGUI
    ../Tavern/vendor/imgui/imconfig.h
    ../Tavern/vendor/imgui/imgui.cpp
    ../Tavern/vendor/imgui/imgui.h
    ../Tavern/vendor/imgui/imgui_demo.cpp
    ../Tavern/vendor/imgui/imgui_draw.cpp
    ../Tavern/vendor/imgui/imgui_internal.h
    ../Tavern/vendor/imgui/imgui_tables.cpp
    ../Tavern/vendor/imgui/imgui_widgets.cpp
    ../Tavern/vendor/imgui/imstb_rectpack.h
    ../Tavern/vendor/imgui/imstb_textedit.h
    ../Tavern/vendor/imgui/imstb_truetype.h

    ../Tavern/vendor/imgui/backends/imgui_impl_glfw.cpp
    ../Tavern/vendor/imgui/backends/imgui_impl_glfw.h
    ../Tavern/vendor/imgui/backends/imgui_impl_opengl3.cpp
    ../Tavern/vendor/imgui/backends/imgui_impl_opengl3.h

    ../Tavern/vendor/imgui/misc/debuggers/imgui.natvis
    ../Tavern/vendor/imgui/misc/debuggers/imgui.natstepfilter

    ../Tavern/vendor/imgui/misc/cpp/imgui_stdlib.cpp
    ../Tavern/vendor/imgui/misc/cpp/imgui_stdlib.h
)
set(VENDOR_IMGUIFILEDIALOG
    ../Tavern/vendor/ImGuiFileDialog/ImGuiFileDialog.cpp
)

source_group(src/Taverner FILES ${SOURCES_TAVERNER})
source_group(vendor/imgui FILES ${VENDOR_IMGUI})
source_group(vendor/ImGuiFileDialog FILES ${VENDOR_IMGUIFILEDIALOG})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Taverner)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Taverner)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/Taverner)

add_executable(Taverner 
    ${SOURCES_TAVERNER}
    ${SOURCES_TAVERNER_WINDOWS}
    ${VENDOR_IMGUI}
    ${VENDOR_IMGUIFILEDIALOG}
    CMakeLists.txt
)

target_include_directories(Taverner PRIVATE 
	${CMAKE_SOURCE_DIR}/Tavern/src
	${CMAKE_SOURCE_DIR}/Tavern/vendor/spdlog/include	
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/Glad/include
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/imgui
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/imgui/backends
    ${CMAKE_SOURCE_DIR}/Tavern/vendor/ImGuiFileDialog
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
