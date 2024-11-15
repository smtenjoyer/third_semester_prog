cmake_minimum_required(VERSION 3.10)
project(physics)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH} /path/to/SFML") # Uncomment and set the path to SFML if it's not in standard locations

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

if (SFML_FOUND)
    message(STATUS "The SFML installed in the system will be used")
else ()
    # If SFML is not found, download and build from source
    message(STATUS "Get SFML from the source code")
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    set(WARNINGS_AS_ERRORS FALSE CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SFML)
endif ()

# Add executable
add_executable(physics
        main.cpp World.cpp Ball.cpp Physics.cpp Color.cpp Painter.cpp Dust.cpp
        black_box/Application.cpp black_box/View.cpp black_box/PainterImpl.cpp)

# Link SFML libraries
target_link_libraries(physics PRIVATE sfml-graphics)

# Compile options
target_compile_options(physics PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

# Include directories
target_include_directories(physics PRIVATE ${SFML_INCLUDE_DIR})

# Copy resources to build directory
add_custom_command(TARGET physics PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
        COMMENT "Copying resources to build directory")

# Packaging (assuming you have a 'package' target defined)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_target(package
            COMMAND ${CMAKE_COMMAND} --build. --target package
            COMMENT "Creating package")
endif ()