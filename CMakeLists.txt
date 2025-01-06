cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(matrix VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

add_executable(matrix_cli matrix.cpp)
add_library(matrix matrix.cpp
        matrix.cpp)

set_target_properties(matrix_cli matrix PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(matrix
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(matrix_cli PRIVATE
    matrix
)

if (MSVC)
    target_compile_options(matrix_cli PRIVATE
        /W4
    )
    target_compile_options(matrix PRIVATE
        /W4
    )
else ()
    target_compile_options(matrix_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(matrix PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS matrix_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

