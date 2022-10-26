cmake_minimum_required(VERSION 2.6)
project("folly_test" C CXX)

set(HOME ${CMAKE_CURRENT_SOURCE_DIR})
# 调试信息
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_VERBOSE_MAKEFILE ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)

# 指定头文件搜索路径
INCLUDE_DIRECTORIES(/opt/vesoft/third-party/3.0/include)
# 指定引用的外部库的搜索路径
LINK_DIRECTORIES(/opt/vesoft/third-party/3.0/lib)


set(GTEST_LIB
    gtest
    pthread
    )

# 子目录
add_subdirectory(src)
