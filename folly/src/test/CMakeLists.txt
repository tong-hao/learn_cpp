
add_executable(test-future1 FutureTest1.cpp)
target_link_libraries(test-future1 ${FOLLY_LIBRARIES} )


add_executable(test1 Test1.cpp)
target_link_libraries(test1 ${FOLLY_LIBRARIES} )

