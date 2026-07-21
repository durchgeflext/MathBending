
add_executable(dieharderSFMT dieharderSFMT.cpp)
target_link_libraries(dieharderSFMT PRIVATE lib_random)

add_executable(SFMTvsSTD SFMTvsSTD.cpp)
target_link_libraries(SFMTvsSTD PRIVATE lib_random)