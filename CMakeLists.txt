cmake_minimum_required(VERSION 3.22)

set(PRJ_NAME NESemu)

project(${PRJ_NAME})
add_executable(${PRJ_NAME} main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#[[ GoogleTest: # there is a problem with imgui, fix this.
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

target_link_libraries(${PRJ_NAME} PRIVATE GTest::gtest) #]]

# CPU:
add_subdirectory(src/CPU) # can it be done another way?
target_include_directories(${PRJ_NAME} PRIVATE src/CPU/inc)
target_link_libraries(${PRJ_NAME} PRIVATE CPU)

# Debugger:
add_subdirectory(src/Debugger) # can it be done another way?
target_include_directories(${PRJ_NAME} PRIVATE src/Debugger/inc)
target_link_libraries(${PRJ_NAME} PRIVATE DebuggerImgui)

# Util:
add_subdirectory(src/incGlobal) # can it be done another way?
target_include_directories(${PRJ_NAME} PRIVATE src/incGlobal)
target_link_libraries(${PRJ_NAME} PRIVATE Util)

# RomLoader:
add_subdirectory(src/RomLoader) # can it be done another way?
target_include_directories(${PRJ_NAME} PRIVATE src/RomLoader/inc)
target_link_libraries(${PRJ_NAME} PRIVATE RomLoader)
