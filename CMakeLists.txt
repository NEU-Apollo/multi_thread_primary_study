cmake_minimum_required(VERSION 3.10.0)
project(multi_thread_exercise)

set(CMAKE_CXX_STANDARD 17)

add_executable(test1 test1.cpp)
target_link_libraries(test1 pthread)

add_executable(test2 test2.cpp)
target_link_libraries(test2 pthread)

add_executable(test3 test3.cpp)
target_link_libraries(test3 pthread)

add_executable(test4 test4.cpp)
target_link_libraries(test4 pthread)