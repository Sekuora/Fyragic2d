# CMakeList.txt : CMake project for Fyragic2d, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.29)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

### Compiler Flags ###


### vcpkg toolchain file ### 
set(VCPKG_DIR "${CMAKE_SOURCE_DIR}/.vessel/externals/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

###

### Set Project Directories ###

# Include Files
set(ENGINE_CORE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Engine/Core/Include")

# Engine Core 
set(ENGINE_CORE_DIR "${CMAKE_SOURCE_DIR}/Engine/Core")

###

# Setup Project
project ("Fyragic2D")

# Find and link dependencies as specified by VCPKG

# Package Dependencies
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(Lua REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# Path Dependencies
find_path(SOL2_INCLUDE_DIRS "sol/abort.hpp")

# Glob all from source dir
file(GLOB Sources "Engine/*.cpp")
file(GLOB_RECURSE EngineSources "${ENGINE_CORE_DIR}/*.cpp")
file(GLOB Includes "Engine/Core/Include/*.h""Engine/Core/Include/*.hpp")

## Clean Binary Directory   
add_custom_target(CleanBuild
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/*
    COMMENT "Cleaning build files"
)

# Add sources to this project's executable.
add_executable (${CMAKE_PROJECT_NAME} ${Sources} ${EngineSources})

add_dependencies(${CMAKE_PROJECT_NAME} CleanBuild)

### Include Files / Headers Directories

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${ENGINE_CORE_INCLUDE_DIR})

### External Dependencies Include Directories

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${LUA_INCLUDE_DIR} ${SOL2_INCLUDE_DIRS})

### External Dependencies Link Libraries

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf-shared imgui::imgui ${LUA_LIBRARIES} glm::glm-header-only)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>)


### Set Resources / Assets Folder. ###

# Define the resources folder to be copied onto the compiled project folder
file(COPY "${PROJECT_SOURCE_DIR}/Resources" DESTINATION "${CMAKE_BINARY_DIR}")