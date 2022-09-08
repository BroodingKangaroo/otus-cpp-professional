cmake_minimum_required(VERSION 3.12)

set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(hw-03-allocator VERSION ${PROJECT_VERSION})

add_executable(hw-03-allocator main.cpp)

add_library(allocator_lib allocator.cpp)
add_library(container_lib container.cpp)

set_target_properties(hw-03-allocator allocator_lib container_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(hw-03-allocator
    allocator_lib
    container_lib
)

install(TARGETS hw-03-allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT max.golovatyi@gmail.com)
include(CPack)