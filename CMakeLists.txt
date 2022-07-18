cmake_minimum_required(VERSION 3.12)

project(otus-cpp-professional LANGUAGES CXX)

# This command should be in the source directory root because ctest expects to find a test file in the build directory root.
# It should be placed before adding testing subdirectory.
enable_testing()

add_subdirectory(hw-01-helloworld)