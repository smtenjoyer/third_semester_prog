cmake_minimum_required(VERSION 3.5.0)
project(ProgLaba3 VERSION 0.1.0 LANGUAGES C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)  # or change to 17 if you're using C++17 features
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(ProgLaba3 main.cpp)

# Include CPack for packaging
include(CPack)

# Optional: If you want to enable testing, keep this section
include(CTest)
enable_testing()

# Set up packaging information
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# Specify the package format (optional)
set(CPACK_GENERATOR "ZIP")  # Specify ZIP for macOS packaging