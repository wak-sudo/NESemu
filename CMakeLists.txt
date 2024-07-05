cmake_minimum_required(VERSION 3.22)

set(PRJ_NAME NESemu)

project(${PRJ_NAME})
add_executable(${PRJ_NAME} main.cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GoogleTest:
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        f8d7d77c06936315286eb55f8de22cd23c188571 # 1.14.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

include(GoogleTest)
gtest_discover_tests(${PRJ_NAME})

target_link_libraries(${PRJ_NAME} PRIVATE GTest::gtest)

# SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(${PRJ_NAME} PRIVATE SDL2 SDL2main)
target_include_directories(${PRJ_NAME} PRIVATE ${SDL2_INCLUDE_DIRS}) # it seems that SDL2_INCLUDE_DIRS is already defined.

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PRJ_NAME} PRIVATE OpenGL::GL)
target_include_directories(${PRJ_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS}) 

# Imgui
set(IMGUI_DIR extLibs/imgui)
set(IMGUI_SRC
   ${IMGUI_DIR}/imgui_impl_opengl3.cpp
   ${IMGUI_DIR}/imgui_impl_sdl2.cpp
   ${IMGUI_DIR}/imgui.cpp
   ${IMGUI_DIR}/imgui_demo.cpp
   ${IMGUI_DIR}/imgui_draw.cpp
   ${IMGUI_DIR}/imgui_tables.cpp
   ${IMGUI_DIR}/imgui_widgets.cpp)

target_include_directories(${PRJ_NAME} PRIVATE ${IMGUI_DIR})
target_sources(${PRJ_NAME} PRIVATE ${IMGUI_SRC})

# CPU:
add_subdirectory(src/CPU) # can it be done another way?
target_include_directories(${PRJ_NAME} PRIVATE src/CPU/inc)
target_link_libraries(${PRJ_NAME} PRIVATE CPU)