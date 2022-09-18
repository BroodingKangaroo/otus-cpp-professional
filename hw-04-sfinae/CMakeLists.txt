cmake_minimum_required(VERSION 3.12)

set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(hw-04-sfinae VERSION ${PROJECT_VERSION})

add_executable(hw-04-sfinae main.cpp)

add_executable(hw-04-tests tests.cpp)

set_target_properties(hw-04-sfinae hw-04-tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(hw-04-tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hw-04-tests
  PROPERTIES
    LABELS "unit"
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
)

install(TARGETS hw-04-sfinae RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT max.golovatyi@gmail.com)
include(CPack)