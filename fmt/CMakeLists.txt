cmake_minimum_required(VERSION 3.10)
# SET(CMAKE_TOOLCHAIN_FILE "/Users/ht/software/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(fmt)
set(CMAKE_VERBOSE_MAKEFILE ON)
find_package(fmt CONFIG REQUIRED)

add_executable(test src/main.cpp)
target_compile_features(test PRIVATE cxx_std_11)
set_target_properties(test PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(test PRIVATE fmt::fmt)


# cmake .. "-DCMAKE_TOOLCHAIN_FILE=/Users/ht/software/vcpkg/scripts/buildsystems/vcpkg.cmake"
