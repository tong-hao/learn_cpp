cmake_minimum_required(VERSION 3.10)

project(main)
set(HOME ${CMAKE_CURRENT_SOURCE_DIR})
# 调试信息
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_VERBOSE_MAKEFILE ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# 设置生成的共享库的名称和类型
add_executable(main Main.cpp)
target_link_libraries(main dl)
