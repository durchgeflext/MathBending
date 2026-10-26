
add_executable(dieharderSFMT dieharderSFMT.cpp)
target_link_libraries(dieharderSFMT PRIVATE lib_random)
target_compile_definitions(dieharderSFMT PRIVATE "${MB_PR_DEF}")

add_executable(SFMTvsSTD SFMTvsSTD.cpp)
target_link_libraries(SFMTvsSTD PRIVATE lib_random)