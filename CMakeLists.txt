cmake_minimum_required(VERSION 3.12)

# set default version if building locally
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")

project(otus-cpp-professional LANGUAGES CXX)

# Google test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# This command should be in the source directory root because ctest expects to find a test file in the build directory root.
# It should be placed before adding testing subdirectory.
enable_testing()

add_subdirectory(hw-01-helloworld)
add_subdirectory(hw-02-ip_filter)