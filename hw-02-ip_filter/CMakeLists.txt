cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")

set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(hw-02-ip_filter VERSION ${PROJECT_VERSION})

add_executable(ip_filter_cli main.cpp)

add_library(ip_filter_lib ip_filter.cpp)

set_target_properties(ip_filter_cli ip_filter_lib PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(ip_filter_cli PRIVATE
    ip_filter_lib
)

add_executable(tests tests.cpp)

set_target_properties(tests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

find_package(OpenSSL REQUIRED COMPONENTS Crypto)

target_link_libraries(tests
    GTest::gtest_main
    OpenSSL::Crypto
    ip_filter_lib
)

include(GoogleTest)
gtest_discover_tests(tests
  PROPERTIES
    LABELS "unit"
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
)

install(TARGETS ip_filter_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT max.golovatyi@gmail.com)
include(CPack)