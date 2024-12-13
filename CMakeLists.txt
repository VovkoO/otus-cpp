cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(print_ip VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

add_executable(print_ip_cli print_ip.cpp)
add_library(print_ip print_ip.cpp)

set_target_properties(print_ip_cli print_ip PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(print_ip
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(print_ip_cli PRIVATE
    print_ip
)

if (MSVC)
    target_compile_options(print_ip_cli PRIVATE
        /W4
    )
    target_compile_options(print_ip PRIVATE
        /W4
    )
else ()
    target_compile_options(print_ip_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(print_ip PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS print_ip_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

