cmake_minimum_required(VERSION 2.8)
project(ThreadSafeQueue)

link_libraries(pthread)
add_executable(testThreadSafeQueue testThreadSafeQueue.cpp)
add_executable(testThreadSafeQueue2 testThreadSafeQueue2.cpp)
add_executable(testThreadSafeStack testThreadSafeStack.cpp)
add_executable(test_move test_move.cpp)

add_test(testThreadSafeQueue testThreadSafeQueue)
add_test(testThreadSafeQueue2 testThreadSafeQueue2)
add_test(testThreadSafeStack testThreadSafeStack)
add_test(test_move test_move)