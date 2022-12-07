cmake_minimum_required(VERSION 3.10)

project(cpp_primer)
set(HOME ${CMAKE_CURRENT_SOURCE_DIR})
# 调试信息
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_VERBOSE_MAKEFILE ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)


add_subdirectory(src/ch01_beginning)
add_subdirectory(src/ch02_var_type)
add_subdirectory(src/ch03_string_vector_array)
add_subdirectory(src/ch04_expression)
add_subdirectory(src/ch05_sentence)
add_subdirectory(src/ch06_funtion)
add_subdirectory(src/ch07_class)
add_subdirectory(src/ch08_io)
add_subdirectory(src/ch09_container)
add_subdirectory(src/ch10_algorithm)
add_subdirectory(src/ch11_map)
add_subdirectory(src/ch12_memory)
