cmake_minimum_required(VERSION 3.16)

project(MathBending VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(MB_PR_DEF "MATHBENDING_PROJECT_ROOT=\"${PROJECT_SOURCE_DIR}\"")

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

# ======================
# Compiler Flags
# ======================
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(lib_random INTERFACE -march=native)
  target_compile_options(lib_util INTERFACE -march=native)
  message(STATUS "Enabled native cpu instructions")
elseif(MSVC AND CMAKE_SYSTEM_NAME STREQUAL "Windows")
  include(CheckCXXSourceRuns)
  check_cxx_source_runs(
      [=[
      #include <windows.h>

      #ifndef PF_AVX2_INSTRUCTIONS_AVAILABLE
      #define PF_AVX2_INSTRUCTIONS_AVAILABLE 40
      #endif

      int main() {
        return IsProcessorFeaturePresent(PF_AVX2_INSTRUCTIONS_AVAILABLE) ? 0 : 1;
      }
      ]=] MATHBENDING_HOST_HAS_AVX2
  )
  if(MATHBENDING_HOST_HAS_AVX2)
    target_compile_options(lib_random INTERFACE /arch:AVX2)
    target_compile_options(lib_util INTERFACE /arch:AVX2)
  endif()
endif()


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
  # =======================
  # Code Coverage Support
  # =======================
  option(ENABLE_COVERAGE "Enable code coverage" ON)

  if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
      add_compile_options(--coverage -O0 -g)
      add_compile_options(-fno-elide-constructors)
      add_link_options(--coverage)
    else()
      message(WARNING "Code coverage is only supported for GCC and Clang")
    endif()
  endif()
  include(FetchContent)
  FetchContent_Declare(
          Catch2
          GIT_REPOSITORY https://github.com/catchorg/Catch2.git
          GIT_TAG v3.4.0
  )
  FetchContent_MakeAvailable(Catch2)

  enable_testing()
  add_subdirectory(test)
endif()

if (BUILD_BENCHMARKS)
  message(STATUS "Enabled benchmarking")
  add_subdirectory(benchmark)
endif()
