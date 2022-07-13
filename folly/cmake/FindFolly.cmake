find_path(FOLLY_ROOT_DIR
    NAMES include/folly/folly-config.h
)

find_library(FOLLY_LIBRARIES
    NAMES folly
    HINTS ${FOLLY_ROOT_DIR}/lib
)

find_library(FOLLY_BENCHMARK_LIBRARIES
    NAMES follybenchmark
    HINTS ${FOLLY_ROOT_DIR}/lib
)

find_path(FOLLY_INCLUDE_DIR
    NAMES folly/folly-config.h
    HINTS ${FOLLY_ROOT_DIR}/include
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Folly DEFAULT_MSG
    FOLLY_LIBRARIES
    FOLLY_INCLUDE_DIR
)


if(GLOG_FOUND)
  set(FOLLY_INCLUDE_DIR ${FOLLY_INCLUDE_DIR})
  set(FOLLY_LIBRARIES ${FOLLY_LIBRARIES})
  message(STATUS "Found folly    (include: ${FOLLY_INCLUDE_DIR}, library: ${FOLLY_LIBRARIES})")
  mark_as_advanced(FOLLY_ROOT_DIR FOLLY_LIBRARIES FOLLY_BENCHMARK_LIBRARIES FOLLY_INCLUDE_DIR)
endif()