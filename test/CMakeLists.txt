include(Catch)

add_executable(test_128integer integer128_test.cpp)
target_link_libraries(test_128integer PRIVATE lib_util Catch2::Catch2WithMain)

add_executable(test_bitShift bitShift_test.cpp)
target_link_libraries(test_bitShift PRIVATE lib_random lib_util Catch2::Catch2WithMain)

add_executable(test_random random_test.cpp)
target_link_libraries(test_random PRIVATE lib_random Catch2::Catch2WithMain)

# Register tests with CTest for CLion discovery
catch_discover_tests(test_128integer)
catch_discover_tests(test_bitShift)
catch_discover_tests(test_random)
