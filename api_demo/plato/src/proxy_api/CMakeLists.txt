
message(STATUS "include路径：${GRAPH_INCLUDE_DIR}")
# 动态库
add_library(graph SHARED graph.cpp ../plato.cpp)
# target_include_directories(graph PUBLIC ${GRAPH_INCLUDE_DIR})
SET_TARGET_PROPERTIES (graph PROPERTIES CLEAN_DIRECT_OUTPUT 1.0)
#SET_TARGET_PROPERTIES (hello PROPERTIES VERSION 1.2 SOVERSION 1)

# 静态库
#add_library(hello_static STATIC hello.cpp)
#SET_TARGET_PROPERTIES (hello_static PROPERTIES OUTPUT_NAME "hello")
#SET_TARGET_PROPERTIES (hello_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)


# TARGETS选项指定要安装的目标
# LIBRARY DESTINATION选项表示将库文件安装到lib目录中
# ARCHIVE DESTINATION选项表示将库文件的静态版本（如果有）也安装到lib目录中
INSTALL (TARGETS graph LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
INSTALL (FILES  graph.h DESTINATION include/)

