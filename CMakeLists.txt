# CMakeList.txt : CMake project for Fyragic2d, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.29)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)


### vcpkg toolchain file ### 
set(VCPKG_DIR "${CMAKE_SOURCE_DIR}/.vessel/externals/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

###

### Set Project Directories ###

###

# Setup Project
project ("Fyragic2D")

# Find and link dependencies as specified by VCPKG
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(Lua REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

find_path(SOL2_INCLUDE_DIRS "sol/abort.hpp")



# Glob all from source dir
file(GLOB Sources "Source/*.cpp")
file(GLOB Includes "Source/Include/*.h")


# Add sources to this project's executable.
add_executable (${CMAKE_PROJECT_NAME} ${Sources} ${Includes})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${LUA_INCLUDE_DIR} ${SOL2_INCLUDE_DIRS})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf-shared imgui::imgui ${LUA_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME}  PRIVATE $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glm::glm-header-only)
