

add_executable(assert_test AssertTest.cpp)
target_link_libraries(assert_test ${GTEST_LIB} )
add_test(NAME assert_test COMMAND assert_test)
