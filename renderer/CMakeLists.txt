# Set up the minimum version of cmake
cmake_minimum_required(VERSION 3.0.0)

# Set the project name and version
set(PROJECT_RENDERER_NAME ${PROJECT_NAME}_Renderer)

project(${PROJECT_RENDERER_NAME})

message("Building ${PROJECT_RENDERER_NAME}...")

add_subdirectory(libs)

# Compile Target
set(SOURCES
  sources/Context/Renderer.cpp
  sources/Context/Window.cpp
  sources/Context/Inputs.cpp
  sources/Context/State.cpp

  sources/Drawing/Camera.cpp
  sources/Drawing/Shader.cpp
  sources/Drawing/Shapes.cpp

  sources/Mesh/Mesh.cpp
  sources/Mesh/Vertex.cpp
  sources/Mesh/VertexCol.cpp
  sources/Mesh/VertexTex.cpp

  sources/Overlay/Overlay.cpp
  sources/Overlay/ImGuiHelper.cpp

  sources/Overlay/Gui/GuiManager.cpp
  sources/Overlay/Gui/GuiTheme.cpp
  sources/Overlay/Gui/GuiModule.cpp

  sources/Overlay/Gui/Windows/GuiMenu.cpp
  sources/Overlay/Gui/Windows/GuiSelection.cpp
  sources/Overlay/Gui/Windows/GuiSettings.cpp

  sources/Overlay/Gui/Popups/GuiClearSystem.cpp

  sources/Serialization/FileManager.cpp
  sources/Serialization/Serialization.cpp
)

set(HEADERS
  include/Context/Renderer.hpp
  include/Context/Window.hpp
  include/Context/Inputs.hpp
  include/Context/State.hpp

  include/Drawing/Camera.hpp
  include/Drawing/Shader.hpp
  include/Drawing/Shapes.hpp

  include/Mesh/Mesh.hpp
  include/Mesh/Vertex.hpp
  include/Mesh/VertexCol.hpp
  include/Mesh/VertexTex.hpp

  include/Overlay/Overlay.hpp
  include/Overlay/ImGuiHelper.hpp

  include/Overlay/Gui/GuiManager.hpp
  include/Overlay/Gui/GuiTheme.hpp
  include/Overlay/Gui/GuiModule.hpp

  include/Serialization/FileManager.hpp
  include/Serialization/Serialization.hpp
)

set(RESSOURCES
  assets/shaders/imgui/fs_imgui.bin.hpp
  assets/shaders/imgui/vs_imgui.bin.hpp

  assets/shaders/default/fs_shaders/fs_base_dx9.bin.hpp
  assets/shaders/default/fs_shaders/fs_base_dx11.bin.hpp
  assets/shaders/default/fs_shaders/fs_base_essl.bin.hpp
  assets/shaders/default/fs_shaders/fs_base_glsl.bin.hpp
  assets/shaders/default/fs_shaders/fs_base_metal.bin.hpp

  assets/shaders/default/vs_shaders/vs_base_dx9.bin.hpp
  assets/shaders/default/vs_shaders/vs_base_dx11.bin.hpp
  assets/shaders/default/vs_shaders/vs_base_essl.bin.hpp
  assets/shaders/default/vs_shaders/vs_base_glsl.bin.hpp
  assets/shaders/default/vs_shaders/vs_base_metal.bin.hpp

  assets/shaders/default/fs_shaders/fs_base_dx9.bin.hpp
  assets/shaders/default/fs_shaders/fs_base_dx11.bin.hpp
  assets/shaders/default/fs_shaders/fs_base_essl.bin.hpp
  assets/shaders/default/fs_shaders/fs_base_glsl.bin.hpp
  assets/shaders/default/fs_shaders/fs_base_metal.bin.hpp

  assets/shaders/default/vs_shaders/vs_base_dx9.bin.hpp
  assets/shaders/default/vs_shaders/vs_base_dx11.bin.hpp
  assets/shaders/default/vs_shaders/vs_base_essl.bin.hpp
  assets/shaders/default/vs_shaders/vs_base_glsl.bin.hpp
  assets/shaders/default/vs_shaders/vs_base_metal.bin.hpp

  assets/icon/ricon.hpp
)

set(FONTS
  assets/fonts/roboto.hpp
  assets/fonts/proggy.hpp
  assets/fonts/consolas.hpp
  assets/fonts/forkawersome.hpp
  assets/fonts/icons.hpp
)

add_library(${PROJECT_RENDERER_NAME} STATIC ${SOURCES} ${HEADERS} ${RESSOURCES} ${FONTS})
target_include_directories(${PROJECT_RENDERER_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# add_subdirectory(examples)
if(BUILD_SHADERS)
  add_subdirectory(assets/shaders)
endif()

if(EMSCRIPTEN)
  target_link_libraries(${PROJECT_RENDERER_NAME} PUBLIC "-s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
  target_link_libraries(${PROJECT_RENDERER_NAME} PUBLIC "-s USE_WEBGL2=1")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
else()
  target_link_libraries(${PROJECT_RENDERER_NAME} PUBLIC glfw)
  target_link_libraries(${PROJECT_RENDERER_NAME} PUBLIC libglew_static)
endif()

target_link_libraries(${PROJECT_RENDERER_NAME} PUBLIC glm)
target_link_libraries(${PROJECT_RENDERER_NAME} PRIVATE freetype)
target_link_libraries(${PROJECT_RENDERER_NAME} PUBLIC imgui)
target_link_libraries(${PROJECT_RENDERER_NAME} PUBLIC bgfx)
target_link_libraries(${PROJECT_RENDERER_NAME} PUBLIC cereal)
