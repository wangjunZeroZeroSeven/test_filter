
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.10)
project(test_filter VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(test_filter main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)