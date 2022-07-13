add_executable(one_example one_example/Server.cpp one_example/MyHandler.cpp one_example/NoFoundHandler.cpp)
target_link_libraries(one_example ${PROXYGEN_LIBRARIES} )