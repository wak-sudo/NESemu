cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PRJ_NAME Util)

project(${PRJ_NAME})

add_library(${PRJ_NAME} STATIC Util.cpp)
target_include_directories(${PRJ_NAME} PUBLIC .)