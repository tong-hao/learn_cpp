cmake_minimum_required(VERSION 3.16)
project(s3-client)
SET(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(CMAKE_VERBOSE_MAKEFILE ON)

# 指定头文件搜索路径
INCLUDE_DIRECTORIES(/home/caton.hao/s3_installed/include)
# 指定引用的外部库的搜索路径
LINK_DIRECTORIES(/home/caton.hao/s3_installed/lib)

# set(AWS_CPP_SDK_INCLUDE_DIRS /home/caton.hao/s3_installed/include/aws CACHE STRING "aws-cpp-sdk include directories")
# set(AWS_CPP_SDK_CORE_LIB "-l:/home/caton.hao/s3_installed/lib/libaws-cpp-sdk-core.so" CACHE STRING "aws-cpp-sdk link core lib")
# set(AWS_CPP_SDK_S3_LIB "-l:/home/caton.hao/s3_installed/lib/libaws-cpp-sdk-s3.so" CACHE STRING "aws-cpp-sdk link S3 lib")

# 指定可执行文件存放目录
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)

ADD_SUBDIRECTORY(src)
