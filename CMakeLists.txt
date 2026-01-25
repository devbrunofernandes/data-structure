cmake_minimum_required(VERSION 3.20)
project(DataStructures C)

set(CMAKE_C_STANDARD 99)
include_directories(include)

file(GLOB_RECURSE LIB_SOURCES "src/*.c")

file(GLOB EXAMPLE_SOURCES "examples/*.c" "examples/*/*.c" "examples/*/*/*.c")

foreach(SOURCE_FILE ${EXAMPLE_SOURCES})
    get_filename_component(EXE_NAME ${SOURCE_FILE} NAME_WE)
    add_executable(${EXE_NAME} ${SOURCE_FILE} ${LIB_SOURCES})
    target_include_directories(${EXE_NAME} PRIVATE include)
endforeach()