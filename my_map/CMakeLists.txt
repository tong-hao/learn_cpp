cmake_minimum_required(VERSION 3.10)

project(my_map)
set(HOME ${CMAKE_CURRENT_SOURCE_DIR})
# 调试信息
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_VERBOSE_MAKEFILE ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)

include_directories(
    ${PROJECT_SOURCE_DIR}/../utils/src/
)

# link_directories(
#     ${PROJECT_SOURCE_DIR}/../3rd/gflags/lib/
#     ${PROJECT_SOURCE_DIR}/../3rd/glog/lib/
# )

# add_subdirectory(src/xxx)
add_executable(std_map src/std_map.cpp)
add_executable(VectorLiteTest src/VectorLiteTest.cpp)

