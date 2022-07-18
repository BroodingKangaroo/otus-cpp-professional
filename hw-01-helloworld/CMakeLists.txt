cmake_minimum_required(VERSION 3.12)

# set default version if building locally
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")

# set project version
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

# set name and version of the project
project(hw-01-helloworld VERSION ${PROJECT_VERSION})

# configure a header file to pass version number to the source code
configure_file(version.h.in version.h)

# add executable
add_executable(helloworld_cli main.cpp)

# create static library; to create dynamic library use add_library(helloworld_lib SHARED lib.cpp)
add_library(helloworld_lib lib.cpp)

# enable support for a specific C++ standard
set_target_properties(helloworld_cli helloworld_lib PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# since the configured header (version.h in this case) will be written to the build directory,
# we must add that directory to the list of paths to search for include files
target_include_directories(helloworld_lib PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

# link the library helloworld_lib to the executable helloworld_cli
target_link_libraries(helloworld_cli PRIVATE
    helloworld_lib
)

add_executable(test_version test_version.cpp)

# Google test requires at least C++14
set_target_properties(test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(test_version
    GTest::gtest_main
    helloworld_lib
)

include(GoogleTest)
gtest_discover_tests(test_version)
add_test(test_version test_version)

# created build directory to store all the build files
# cmake .. (from /build directory) - run cmake to generate files for building the project (e.g. Makefile, CMakeCache.txt, *.sln, etc.)
# cmake --build . (from /build directory) - build the project (e.g. make)
# cmake --build . --target helloworld_cli - build the specific target
# cmake --install . (from /build directory) - install the project (e.g. make install)
# cmake --open . (from /build directory) - open the project in Visual Studio