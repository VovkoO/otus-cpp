cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

project(async)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_library(async SHARED src/async.cpp)

install(TARGETS async LIBRARY DESTINATION lib)

install(FILES include/async.h DESTINATION include/async)

add_executable(async_app app/main.cpp)

target_link_libraries(async_app async)

install(TARGETS async_app RUNTIME DESTINATION bin)