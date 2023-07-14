
message(status "目录：${CMAKE_CURRENT_LIST_DIR}/../include" )
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../include DESTINATION ./)

ADD_SUBDIRECTORY(proxy_api)
