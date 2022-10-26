
# g++ -fPIC -c sum.cpp
# g++ -shared sum.o -o libsum.so
add_library(sum SHARED
sum.cpp
)

# g++ -o main main.cpp -ldl
add_executable(main main.cpp)
target_link_libraries(main dl)
