include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#add_subdirectory(${HOME}/src/common)
add_subdirectory(${HOME}/src/benchmark)
add_subdirectory(${HOME}/src/test)


#⽣成应⽤程序
add_executable(conv-example ConvExample.cpp)
target_link_libraries(conv-example ${FOLLY_LIBRARIES} )

add_executable(atomic-hashmap-example AtomicHashmapExample.cpp)
target_link_libraries(atomic-hashmap-example pthread glog ${FOLLY_LIBRARIES} )

add_executable(dynamic-example DynamicExample.cpp)
target_link_libraries(dynamic-example  glog ${FOLLY_LIBRARIES} )

add_executable(executors-example ExecutorsExample.cpp)
target_link_libraries(executors-example  glog gflags pthread ${FOLLY_LIBRARIES} )


add_executable(fbstring-example FBStringExample.cpp)
target_link_libraries(fbstring-example ${FOLLY_LIBRARIES} )

add_executable(format-example FormatExample.cpp)
target_link_libraries(format-example ${FOLLY_LIBRARIES} )

add_executable(function-example FunctionExample.cpp)
target_link_libraries(function-example ${FOLLY_LIBRARIES} )

add_executable(future-example FuturesExample.cpp)
target_link_libraries(future-example glog gflags pthread ${FOLLY_LIBRARIES} )

add_executable(groupvarint-example GroupVarintExample.cpp)
target_link_libraries(groupvarint-example glog ${FOLLY_LIBRARIES} )


add_executable(histogram-example HistogramExample.cpp)
target_link_libraries(histogram-example glog ${FOLLY_LIBRARIES} )


add_executable(packedsyncptr-example PackedSyncPtrExample.cpp)
target_link_libraries(packedsyncptr-example glog ${FOLLY_LIBRARIES} )


add_executable(queue-example ProducerConsumerQueueExample.cpp)
target_link_libraries(queue-example glog pthread ${FOLLY_LIBRARIES} )

add_executable(smalllock-example SmallLocksExample.cpp)
target_link_libraries(smalllock-example glog gflags pthread ${FOLLY_LIBRARIES} )

add_executable(sync-example SynchronizedExample.cpp)
target_link_libraries(sync-example glog gflags pthread ${FOLLY_LIBRARIES} )


add_executable(threadcachedlint-example ThreadCachedIntExample.cpp)
target_link_libraries(threadcachedlint-example glog gflags pthread ${FOLLY_LIBRARIES} )

add_executable(threadlocal-example ThreadLocalExample.cpp)
target_link_libraries(threadlocal-example glog gflags pthread ${FOLLY_LIBRARIES} )

add_executable(traits-example TraitsExample.cpp)
target_link_libraries(traits-example ${FOLLY_LIBRARIES} )

add_executable(smallvector-example SmallVectorExample.cpp)
target_link_libraries(smallvector-example ${FOLLY_LIBRARIES} )


add_executable(hash_example HashExample.cpp)
target_link_libraries(hash_example ${FOLLY_LIBRARIES} )

add_executable(evicting_cache EvictingCacheMapExample.cpp)
target_link_libraries(evicting_cache ${FOLLY_LIBRARIES} )

add_executable(stop-watch-example StopWatchExample.cpp)
target_link_libraries(stop-watch-example ${FOLLY_LIBRARIES} )

add_executable(xlog-example XLogExample.cpp)
target_link_libraries(xlog-example ${FOLLY_LIBRARIES} )
