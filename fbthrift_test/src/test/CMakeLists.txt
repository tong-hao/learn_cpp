add_executable(
	service_test
	ServiceTest.cpp	
	../thrift_client_pool.cpp
)
target_link_libraries(
	service_test
	hander_lib
	calc-cpp2
	${FBTHRIFT_LIBRARIES}
	gflags
	glog
	${FOLLY_LIBRARIES}
	gtest
	gtest_main
	pthread
)
add_dependencies(service_test calc-cpp2)