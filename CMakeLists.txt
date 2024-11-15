cmake_minimum_required(VERSION 3.10)
project(physics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML (prefer system installation)
find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

if (NOT SFML_FOUND)
    message(STATUS "SFML not found, building from source...")
    include(FetchContent)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
    )
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    set(WARNINGS_AS_ERRORS FALSE CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SFML)
endif()

add_executable(physics
        main.cpp World.cpp Ball.cpp Physics.cpp Color.cpp Painter.cpp Dust.cpp
        black_box/Application.cpp black_box/View.cpp black_box/PainterImpl.cpp
)

target_link_libraries(physics PRIVATE sfml-graphics)

target_compile_options(physics PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

target_include_directories(physics PRIVATE ${SFML_INCLUDE_DIR})


# Install resources
install(FILES resources/* DESTINATION .)  # Install resources to the installation directory

# Create a package (this needs further definition based on your packaging method)
add_custom_target(create_package ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink resources ${CMAKE_INSTALL_PREFIX}/resources
    COMMAND <your_packaging_commands_here>  #Replace with actual commands
    COMMENT "Creating package"
    DEPENDS physics
)

#This section needs more detail based on your packaging strategy
if(MSVC)
    add_custom_command(TARGET physics POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR} "release"
        COMMAND zip -r "release/physics-0.0.${{ github.run_number }}-win64.zip" "release/*"
        COMMENT "Creating Windows Package"
    )
    
    set(PACKAGE_FILE "release/physics-0.0.${{ github.run_number }}-win64.zip")
elseif(UNIX)
    #Add linux packaging commands here - using a tool like cpack would be highly recommended.
    add_custom_target(package ALL
        COMMAND ${CMAKE_COMMAND} -E create_symlink resources ${CMAKE_INSTALL_PREFIX}/resources
        COMMAND make install
        COMMENT "Creating Linux Package"
    )
    set(PACKAGE_FILE "release/physics-0.0.${{ github.run_number }}-Linux.deb")

endif()
