cmake_minimum_required(VERSION 3.2)

PROJECT(calc-fbthrift CXX)


# 显示指定使用的C++编译器
set(CMAKE_CXX_COMPILER "g++")
# c++11             
set(CMAKE_CXX_FLAGS "-std=c++11")
# 调试信息             
set(CMAKE_CXX_FLAGS "-g3")
# 开启所有警告                     
set(CMAKE_CXX_FLAGS "-Wall")
# 调试包不优化                  
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
# release包优化
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(HOME ${CMAKE_CURRENT_SOURCE_DIR})
# 编译结果输出目录
set(EXECUTABLE_OUTPUT_PATH ${HOME}/build/bin)
set(LIBRARY_OUTPUT_PATH ${HOME}/build/lib)

include(cmake/ThriftLibrary.cmake)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include_directories("${PROJECT_SOURCE_DIR}/src")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -fprofile-arcs -ftest-coverage ")

SET(CMAKE_VERBOSE_MAKEFILE ON)

find_package(FBThrift REQUIRED)
find_package(Folly REQUIRED)
find_package(Gflags REQUIRED)
find_package(Glog REQUIRED)

add_subdirectory(src)

