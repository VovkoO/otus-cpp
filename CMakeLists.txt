cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_KNOWN_FEATURES cxx_std_23)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(bayan LANGUAGES CXX VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

find_package(Boost COMPONENTS program_options REQUIRED)
if (Boost_FOUND)
    message(STATUS "Boost found at: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

add_executable(bayan_cli bayan.cpp)
add_library(bayan bayan.cpp
        file_checker.h
        file_checker.cpp)

target_include_directories(bayan_cli PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(bayan PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(bayan_cli PRIVATE Boost::program_options)
target_link_libraries(bayan_cli PRIVATE bayan)

set_target_properties(bayan_cli bayan PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(bayan_cli PRIVATE /W4)
    target_compile_options(bayan PRIVATE /W4)
else()
    target_compile_options(bayan_cli PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(bayan PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS bayan_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)