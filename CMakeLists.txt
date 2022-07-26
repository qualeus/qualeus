# Set up the minimum version of cmake
cmake_minimum_required(VERSION 3.0.0)

# Set the project name and version
set(PROJECT_NAME "Qualeus")
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 5)
set(PROJECT_VERSION_REVISION 2)

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_REVISION})

message("Building ${PROJECT_NAME} VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_REVISION}...")

# Build targets
option(BUILD_TESTS "Building the engine tests" OFF)
option(BUILD_SHADERS "Building the renderer shaders" ON)
option(BUILD_DOCS "Building only the documentation" OFF)

# Configure dependencies for build static libraries only.
set(BUILD_SHARED_LIBS OFF)

# Set the C++ standard to be used
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add customs Flags
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Werror -Wfatal-errors -O0 -g -rdynamic")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Werror -Wfatal-errors -O3 -s") # -fexpensive-optimizations

# CMake options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set default build type explicitly to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build type." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(BUILD_DOCS)
    add_subdirectory(docs)
elseif(BUILD_TESTS)
    add_subdirectory(engine/tests)
else()
    message("BUILD_SHADERS = ${BUILD_SHADERS}")
    add_executable(${PROJECT_NAME} "main/main.cpp")

    # Setup config file
    configure_file("${PROJECT_SOURCE_DIR}/Config.hpp.in" "${PROJECT_BINARY_DIR}/Config.hpp")
    include_directories("${PROJECT_BINARY_DIR}")

    add_subdirectory(engine)
    target_link_libraries(${PROJECT_NAME} Engine)
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/engine/include")

    add_subdirectory(renderer)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_Renderer)
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/renderer/include")
endif()