cmake_minimum_required(VERSION 3.12)

project(otus-cpp-professional LANGUAGES CXX)

add_subdirectory(hw-01-helloworld)

# Google test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# This command should be in the source directory root because ctest expects to find a test file in the build directory root.
enable_testing()