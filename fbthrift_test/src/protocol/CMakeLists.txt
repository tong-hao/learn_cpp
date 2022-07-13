# search thrift1 executable in default path
find_program(THRIFT1 NAMES thrift1)
find_library(THRIFTCPP2 NAMES thriftcpp2)

if(THRIFT1-NOTFOUND)
    message(FATAL "executable `thrift1` not found")
endif()
if(THRIFTCPP2-NOTFOUND)
    message(FATAL "libray thriftcpp2 not found")
endif()

thrift_library(
    calc
    CalculatorService
    cpp2
    ""
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    "protocol")
