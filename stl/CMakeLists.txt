CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
project("boost_test" C CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

# 显示指定使用的C++编译器
set(CMAKE_CXX_COMPILER "g++")
# c++11             
set(CMAKE_CXX_FLAGS "-std=c++17 -g -Wall")
# 调试包不优化                  
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
# release包优化
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(HOME ${CMAKE_CURRENT_SOURCE_DIR})
SET(PROJECT_ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")  
# 编译结果输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

#include_directories("/opt/vesoft/third-party/3.3/include")
#link_directories("/opt/vesoft/third-party/3.3/lib")



#子目录
add_subdirectory(${HOME}/src/cpp/container)
add_subdirectory(${HOME}/src/c)
add_subdirectory(${HOME}/src/cpp11)
add_subdirectory(${HOME}/src/cpp14)
add_subdirectory(${HOME}/src/cpp17)
