cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PRJ_NAME CPU)

project(${PRJ_NAME})

set(SOURCE_DIR src)
set(OPCODES_SRC_DIR ${SOURCE_DIR}/Opcodes)
set(INCLUDE_DIR inc)

set(SURF_SRC_FILES
    ${SOURCE_DIR}/Cons.cpp
    ${SOURCE_DIR}/Exec.cpp
    ${SOURCE_DIR}/FlagsReg.cpp
    ${SOURCE_DIR}/FunPtr.cpp
    ${SOURCE_DIR}/Loading.cpp
    ${SOURCE_DIR}/StackReg.cpp
    ${SOURCE_DIR}/Tables.cpp)

set(OPCODES_SRC_FILES
    ${OPCODES_SRC_DIR}/Arith.cpp
    ${OPCODES_SRC_DIR}/Bra.cpp
    ${OPCODES_SRC_DIR}/Ctrl.cpp
    ${OPCODES_SRC_DIR}/Flags.cpp
    ${OPCODES_SRC_DIR}/Inc.cpp
    ${OPCODES_SRC_DIR}/Load.cpp
    ${OPCODES_SRC_DIR}/Logical.cpp
    ${OPCODES_SRC_DIR}/Others.cpp
    ${OPCODES_SRC_DIR}/Shift.cpp
    ${OPCODES_SRC_DIR}/Stack.cpp
    ${OPCODES_SRC_DIR}/Trans.cpp)

set(SRC_FILES ${OPCODES_SRC_FILES} ${SURF_SRC_FILES})

add_library(${PRJ_NAME} STATIC ${SRC_FILES})
target_include_directories(${PRJ_NAME} PUBLIC ${INCLUDE_DIR})

# Util
target_include_directories(${PRJ_NAME} PUBLIC ../incGlobal)