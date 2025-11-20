cmake_minimum_required(VERSION 3.16)

project(MathBending VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =======================
# Header-only module: random
# =======================
add_library(lib_random INTERFACE)
add_library(lib_util INTERFACE)

target_include_directories(lib_random
                           INTERFACE
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
)
target_include_directories(lib_util
                           INTERFACE
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
)


target_compile_features(lib_random INTERFACE cxx_std_23)
target_compile_features(lib_util INTERFACE cxx_std_23)


# =======================
# Installation
# =======================
include(GNUInstallDirs)

# Install headers
install(
        DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install interface targets
install(
        TARGETS lib_random lib_util
        EXPORT MathBendingTargets
)

# Install the CMake export file
install(
        EXPORT MathBendingTargets
        NAMESPACE MathBending::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MathBending
)

# -------------------------
# Tests and Benchmarks
# -------------------------
option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_BENCHMARKS "Build benchmarks" OFF)

if (BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

if (BUILD_BENCHMARKS)
  add_subdirectory(benchmark)
endif()
