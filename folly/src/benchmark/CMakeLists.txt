
add_executable(benchmark-example BenchmarkExample.cpp)
target_link_libraries(benchmark-example ${FOLLY_LIBRARIES} )

add_executable(benchmark-queue BenchmarkQueue.cpp)
target_link_libraries(benchmark-queue ${FOLLY_LIBRARIES} )
