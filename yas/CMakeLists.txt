cmake_minimum_required(VERSION 2.6)
project("yas_test" C CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
# 显示指定使用的C++编译器
set(CMAKE_CXX_COMPILER "g++")
# c++11
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")
# 调试包不优化
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
# release包优化
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(HOME ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
# 编译结果输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)

# 指定头文件搜索路径
INCLUDE_DIRECTORIES(/home/caton.hao/build_code/nebula-analytics/3rd/yas/include)
# # 指定引用的外部库的搜索路径
# LINK_DIRECTORIES(/opt/vesoft/third-party/3.0/lib)


# 子目录
add_subdirectory(${HOME}/src)

