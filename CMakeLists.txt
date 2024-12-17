cmake_minimum_required(VERSION 3.28)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
project(boboost VERSION ${PROJECT_VERSION})

find_package(Boost 1.86.0 REQUIRED COMPONENTS program_options system filesystem NO_MODULE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(boboost main.cpp)
target_link_libraries(boboost ${Boost_LIBRARIES}) # Use ${Boost_LIBRARIES}

install(TARGETS boboost DESTINATION bin)

# CPack configuration
set(CPACK_PROJECT_NAME boboost)
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "example@example.com")

# Conditional generator selection based on the operating system
if(APPLE)
    set(CPACK_GENERATOR "Bundle") # Or "DragNDrop" for a more user-friendly installer
    set(CPACK_MACOSX_BUNDLE_EXECUTABLE "boboost") # Ensure this matches your executable name

elseif(UNIX AND NOT APPLE) # Linux
    set(CPACK_GENERATOR "DEB")
endif()



include(CPack)

enable_testing() #Keep this if you have tests