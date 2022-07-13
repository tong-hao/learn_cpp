cmake_minimum_required(VERSION 2.6)
project("folly_test" C CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
# 显示指定使用的C++编译器
set(CMAKE_CXX_COMPILER "g++")
# c++11
set(CMAKE_CXX_FLAGS "-std=c++11")
# 调试信息
set(CMAKE_CXX_FLAGS "-g")
# 开启所有警告
set(CMAKE_CXX_FLAGS "-Wall")
# 调试包不优化
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
# release包优化
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(HOME ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
# 编译结果输出目录
set(EXECUTABLE_OUTPUT_PATH ${HOME}/build/bin)
set(LIBRARY_OUTPUT_PATH ${HOME}/build/lib)

set(FOLLY_LIBRARIES
    folly
    boost_context
    boost_system
    dl
    event
    double-conversion
    z
    lz4
    snappy
    iberty
    fmt
    ssl
    crypto
    pthread
    glog
    gflags)

# 子目录
add_subdirectory(${HOME}/src)

message(STATUS "SRC_LIST:${SRC_LIST}")
