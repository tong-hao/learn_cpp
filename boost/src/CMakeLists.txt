add_subdirectory(http)
add_subdirectory(http_client)

add_executable(JsonTest JsonTest.cpp)

add_executable(test test.cpp)
target_link_libraries(test boost_context boost_system boost_filesystem)

# boost编译的时候没有编译fiber，正确编译：./b2 --with-fiber
# add_executable(FiberTest1 fiber/FiberTest1.cpp)
# target_link_libraries(FiberTest1 -lboost_fiber -lboost_context)
