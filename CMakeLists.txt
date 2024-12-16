cmake_minimum_required(VERSION 3.28)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
project(boboost VERSION ${PROJECT_VESRION})

# cmake_policy(SET CMP0167 NEW) # Set policy for Boost finding

find_package(Boost 1.86.0 REQUIRED COMPONENTS program_options system filesystem NO_MODULE)
set(CMAKE_CXX_STANDARD 17)
add_executable(boboost main.cpp)
target_link_libraries(boboost Boost::program_options Boost::system Boost::filesystem)

set(CXX_STANDARD_REQUIRED ON)

install(TARGETS boboost DESTINATION bin)

set(CPACK_PROJECT_NAME boboost)
set(CPACK_GENERATOR "ZIP;DEB")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

enable_testing()
include(CPack)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

install(TARGETS boboost DESTINATION bin) # Installs the boboost executable to the bin directory

