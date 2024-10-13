cmake_minimum_required(VERSION 3.5.0)
project(ProgLaba3 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(ProgLaba3 main.cpp list.cpp consistent.cpp)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
