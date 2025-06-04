cmake_minimum_required(VERSION 3.10)
project(RegexParser CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(regex_parser main.cpp)

target_link_libraries(regex_parser PRIVATE regex_lib)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(lib)

add_subdirectory(tests)

enable_testing()
