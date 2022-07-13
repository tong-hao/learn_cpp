set(FBTHRIFT_LIBRARIES
    thriftcpp2
    thriftprotocol
    thriftfrozen2
    thriftmetadata
    thrift-core
    async
    protocol
    transport
    concurrency
    wangle
    fizz
    zstd
    ReactiveSocket
    yarpl
    sodium)

set(FOLLY_LIBRARIES
    folly
    boost_context
    boost_system
    dl
    event
    double-conversion
    z
    lz4
    snappy
    iberty
    fmt
    ssl
    crypto
    lzma
    zstd
    pthread)

set(GTEST_LIBRARIES gtest gtest_main)

add_subdirectory(protocol)
add_subdirectory(handler)
add_subdirectory(test)

add_executable(server Server.cpp)
target_link_libraries(server calc-cpp2 hander_lib ${FBTHRIFT_LIBRARIES}
                      ${FOLLY_LIBRARIES})

add_executable(client Client.cpp)
target_link_libraries(client calc-cpp2 ${FBTHRIFT_LIBRARIES} gflags glog
                      ${FOLLY_LIBRARIES})

add_executable(client2 Client2.cpp)
target_link_libraries(client2 calc-cpp2 ${FBTHRIFT_LIBRARIES} gflags glog
                      ${FOLLY_LIBRARIES})

add_executable(client3 Client3.cpp)
target_link_libraries(client3 calc-cpp2 ${FBTHRIFT_LIBRARIES} gflags glog
                      ${FOLLY_LIBRARIES})

add_executable(client31 Client31.cpp)
target_link_libraries(client31 calc-cpp2 ${FBTHRIFT_LIBRARIES} gflags glog
                      ${FOLLY_LIBRARIES})

add_executable(client4 Client4.cpp thrift_client_pool.cpp)
target_link_libraries(client4 calc-cpp2 ${FBTHRIFT_LIBRARIES} gflags glog
                      ${FOLLY_LIBRARIES})
