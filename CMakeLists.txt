cmake_minimum_required(VERSION 3.28)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})  # Corrected typo
project(boboost VERSION ${PROJECT_VERSION})

# cmake_policy(SET CMP0167 NEW) # Set policy for Boost finding

find_package(Boost 1.86.0 REQUIRED COMPONENTS program_options system filesystem NO_MODULE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(boboost main.cpp)
target_link_libraries(boboost Boost::program_options Boost::system Boost::filesystem)

install(TARGETS boboost DESTINATION bin) # Installs the boboost executable to the bin directory

# CPack configuration
set(CPACK_PROJECT_NAME boboost)
set(CPACK_GENERATOR "ZIP;DEB")
set(CPACK_GENERATOR "DEB")
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")

# Extract version components
string(REPLACE "." ";" VERSION_LIST ${PROJECT_VERSION})
list(GET VERSION_LIST 0 CPACK_PACKAGE_VERSION_MAJOR)
list(GET VERSION_LIST 1 CPACK_PACKAGE_VERSION_MINOR)
list(GET VERSION_LIST 2 CPACK_PACKAGE_VERSION_PATCH)

set(CPACK_PACKAGE_CONTACT example@example.com)

enable_testing()
include(CPack)