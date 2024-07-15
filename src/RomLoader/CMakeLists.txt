cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PRJ_NAME RomLoader)

project(${PRJ_NAME})

add_library(${PRJ_NAME} STATIC src/RomLoader.cpp)
target_include_directories(${PRJ_NAME} PUBLIC inc)

# CPU
target_include_directories(${PRJ_NAME} PUBLIC ../CPU/inc)

# Util
target_include_directories(${PRJ_NAME} PUBLIC ../incGlobal)