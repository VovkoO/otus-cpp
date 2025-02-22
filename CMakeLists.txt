cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

project(async)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(async LANGUAGES CXX VERSION ${PROJECT_VESRION})

include_directories(include)

add_library(async SHARED src/async.cpp)

install(TARGETS async LIBRARY DESTINATION lib)

install(FILES include/async.h DESTINATION include/async)

add_executable(async_app app/main.cpp)

target_link_libraries(async_app async)

install(TARGETS async_app RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)