cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PRJ_NAME Debugger)

project(${PRJ_NAME})

# Debugger

set(SOURCE_DIR src)
set(INCLUDE_DIR inc)

set(SRC_FILES
    ${SOURCE_DIR}/Cons.cpp
    ${SOURCE_DIR}/Print.cpp
    ${SOURCE_DIR}/Tables.cpp
    ${SOURCE_DIR}/Debugger.cpp)

add_library(${PRJ_NAME} STATIC ${SRC_FILES})
target_include_directories(${PRJ_NAME} PUBLIC ${INCLUDE_DIR})

# Util

target_include_directories(${PRJ_NAME} PUBLIC ../incGlobal)

# CPU

target_include_directories(${PRJ_NAME} PUBLIC ../CPU/inc)

#ImGui:

set(IMGUI_DIR extLibs/imgui)
set(IMGUI_SRC
   ${IMGUI_DIR}/imgui_impl_opengl3.cpp
   ${IMGUI_DIR}/imgui_impl_sdl2.cpp
   ${IMGUI_DIR}/imgui.cpp
   ${IMGUI_DIR}/imgui_demo.cpp
   ${IMGUI_DIR}/imgui_draw.cpp
   ${IMGUI_DIR}/imgui_tables.cpp
   ${IMGUI_DIR}/imgui_widgets.cpp)

target_include_directories(${PRJ_NAME} PUBLIC ${IMGUI_DIR})
target_sources(${PRJ_NAME} PUBLIC ${IMGUI_SRC})

# SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(${PRJ_NAME} PUBLIC SDL2 SDL2main)
target_include_directories(${PRJ_NAME} PUBLIC ${SDL2_INCLUDE_DIRS}) # SDL2_INCLUDE_DIRS is already defined.

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PRJ_NAME} PUBLIC OpenGL::GL)
target_include_directories(${PRJ_NAME} PUBLIC ${OPENGL_INCLUDE_DIRS}) 
