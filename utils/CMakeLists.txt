cmake_minimum_required(VERSION 3.10)

project(xxx)
set(HOME ${CMAKE_CURRENT_SOURCE_DIR})
# 调试信息
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_VERBOSE_MAKEFILE ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)


# add_subdirectory(src/xxx)
add_executable(TimeTest src/TimeTest.cpp)
add_executable(MemUsageTest src/MemUsageTest.cpp)
