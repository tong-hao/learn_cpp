message(STATUS "-> handler")


add_library(hander_lib
	CalcHandler.h
	CalcHandler.cpp
)
target_link_libraries(hander_lib
	calc-cpp2
	thriftcpp2
	folly
	glog
	gflags
	)