cmake_minimum_required(VERSION 3.14)

project(cub VERSION 1.0.0)

set(TARGET_LIB ${PROJECT_NAME})

option(SHARED      "Generate shared library otherwise static" OFF)
option(ENABLE_TEST "Build tests" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof  -g -std=c++14")

include(${PROJECT_SOURCE_DIR}/cmake/CPM.cmake)

add_subdirectory("src")

if(ENABLE_TEST)
    add_subdirectory(test)
endif()
