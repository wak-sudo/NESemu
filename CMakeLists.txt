cmake_minimum_required(VERSION 3.22)

project(NESemu)

add_subdirectory(src/CPU)
add_executable(main main.cpp)
target_link_libraries(main PRIVATE CPU)