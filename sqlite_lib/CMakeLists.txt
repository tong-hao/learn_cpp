cmake_minimum_required(VERSION 3.10)

project(sqlite_lib)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(unofficial-sqlite3 CONFIG REQUIRED)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE unofficial::sqlite3::sqlite3)

