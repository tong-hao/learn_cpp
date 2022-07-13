

find_path(Googletest_INCLUDE_DIR NAMES gmock gtest)
find_library(Googletest_LIBRARY NAMES libgmock.so libgmock_main.so libgtest.so libgtest_main.so)

if(Googletest_INCLUDE_DIR AND Googletest_LIBRARY)
    set(Googletest_FOUND TRUE)
    mark_as_advanced(
        Googletest_INCLUDE_DIR
        Googletest_LIBRARY
    )
endif()

if(NOT Googletest_FOUND)
    message(FATAL_ERROR "Googletest doesn't exist")
endif()