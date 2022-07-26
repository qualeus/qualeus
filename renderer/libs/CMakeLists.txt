cmake_minimum_required(VERSION 3.12)

include(FetchContent)

SET(BUILD_SHARED_LIBS OFF CACHE BOOL "")

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

FetchContent_Declare(freetype2
  GIT_REPOSITORY https://github.com/aseprite/freetype2.git
  GIT_TAG VER-2-10-0
)

FetchContent_Declare(glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG fce2abd01ce21063bd25ba67c9318be83bf48813
)

FetchContent_Declare(glew
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake
)

FetchContent_Declare(glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG 3.3
)

FetchContent_Declare(imgui
  GIT_REPOSITORY https://github.com/qualeus/imgui_docking_cmake
  GIT_TAG ddecdd7ef60c80e06f7a198466746e89a1f716c5 # docking
)

FetchContent_Declare(bgfx
  GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake
  GIT_TAG b54594715f8d29938d879c1c18108960c4806cb8
)

FetchContent_Declare(cereal
  GIT_REPOSITORY https://github.com/USCiLab/cereal
  GIT_TAG v1.3.2
)

FetchContent_GetProperties(freetype2)

if(NOT freetype2_POPULATED)
  FetchContent_Populate(freetype2)
  set(CMAKE_DISABLE_FIND_PACKAGE_HarfBuzz TRUE)
  set(CMAKE_DISABLE_FIND_PACKAGE_BZip2 TRUE)
  set(CMAKE_DISABLE_FIND_PACKAGE_PNG TRUE)
  set(CMAKE_DISABLE_FIND_PACKAGE_ZLIB TRUE)
  add_subdirectory(${freetype2_SOURCE_DIR} ${freetype2_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_GetProperties(glm)

if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
  add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_GetProperties(glew)

if(NOT glew_POPULATED AND NOT EMSCRIPTEN)
  FetchContent_Populate(glew)
  option(glew-cmake_BUILD_SHARED "Build the shared glew library" OFF)
  set(glew-cmake_BUILD_SHARED OFF)
  add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_GetProperties(glfw)

if(NOT glfw_POPULATED AND NOT EMSCRIPTEN)
  FetchContent_Populate(glfw)
  add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR} EXCLUDE_FROM_ALL)
  target_compile_options(glfw PRIVATE "-w")
endif()

FetchContent_GetProperties(imgui)

if(NOT imgui_POPULATED)
  FetchContent_Populate(imgui)

  add_subdirectory(${imgui_SOURCE_DIR} ${imgui_BINARY_DIR} EXCLUDE_FROM_ALL)

  # FetchContent_MakeAvailable(imgui)
endif()

FetchContent_GetProperties(bgfx)

if(NOT bgfx_POPULATED)
  FetchContent_Populate(bgfx)
  add_subdirectory(${bgfx_SOURCE_DIR} ${bgfx_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_GetProperties(cereal)

if(NOT cereal_POPULATED)
  FetchContent_Populate(cereal)
  add_subdirectory(${cereal_SOURCE_DIR} ${cereal_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
