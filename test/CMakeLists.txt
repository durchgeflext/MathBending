
add_executable(test_128integer integer128_test.cpp)
target_link_libraries(test_128integer PRIVATE lib_util)

add_executable(test_bitShift bitShift_test.cpp)
target_link_libraries(test_bitShift PRIVATE lib_random lib_util)

add_executable(test_random random_test.cpp)
target_link_libraries(test_random PRIVATE lib_random)