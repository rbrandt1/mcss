cmake_minimum_required(VERSION 3.9)
project(tests)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/Catch2)

add_definitions(-DTEST=42)

include_directories(include)

add_executable(test test.cpp ksTest.cpp ${SOURCES})
list(APPEND LIBRARIES Catch2::Catch2)
target_link_libraries(test PUBLIC ${LIBRARIES})
