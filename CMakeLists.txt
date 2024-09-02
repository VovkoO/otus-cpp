cmake_minimum_required(VERSION 3.12)

option(UPDATE_VERSION "<help_text>" OFF)
if (UPDATE_VERSION)
    set(UPDATE_VERSION ON)
endif()


# Auto update the version
# Read the version from version.txt
include(${CMAKE_SOURCE_DIR}/cmake/update_version.cmake)

# Now PROJECT_VERSION contains the current version
set(PROJECT_VERSION_PATCH "${PATCH_VERSION}" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION "${PROJECT_VERSION}")
message(STATUS "PROJECT_VERSION_PATCH: ${PROJECT_VERSION_PATCH}")


project(helloworld VERSION ${PROJECT_VERSION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)
message(STATUS "PROJECT_VERSION_PATCH: ${PROJECT_VERSION_PATCH}")

configure_file(${CMAKE_SOURCE_DIR}/version.h.in ${CMAKE_BINARY_DIR}/version.h @ONLY)

# add_custom_target(update_version
#     COMMAND cd .. && ${CMAKE_COMMAND} -DUPDATE_VERSION=ON -P ${CMAKE_SOURCE_DIR}/cmake/update_version.cmake
#     COMMENT "Updating project version..."
# )

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)

set_target_properties(helloworld_cli helloworld PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(helloworld_cli PRIVATE
    helloworld
)

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(test_version test_version.cpp)

    set_target_properties(test_version PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(test_version PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

    target_link_libraries(test_version
        ${Boost_LIBRARIES}
        helloworld
    )
endif()

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
        /W4
    )
    target_compile_options(helloworld PRIVATE
        /W4
    )
    if(WITH_BOOST_TEST)
        target_compile_options(test_version PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(helloworld PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_BOOST_TEST)
        target_compile_options(test_version PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(test_version test_version)
endif()
