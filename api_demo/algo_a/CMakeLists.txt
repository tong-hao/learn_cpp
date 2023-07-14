cmake_minimum_required(VERSION 3.16)
project(3rd)

SET(ROOT_DIR ${CMAKE_SOURCE_DIR})
# 指定头文件搜索路径
INCLUDE_DIRECTORIES(${ROOT_DIR}/include)
# 指定引用的外部库的搜索路径
LINK_DIRECTORIES(${ROOT_DIR}/lib)
# 指定可执行文件存放目录
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)

ADD_SUBDIRECTORY(src)
