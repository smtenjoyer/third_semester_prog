cmake_minimum_required(VERSION 3.14)
project(GTests)

enable_testing()

include(FetchContent)

# Loading googletest
message(STATUS "Loading googletest...")
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

set(COMMON_SRCS
    "../ipfilter.cpp"  # Ensure this path is correct
)

message(STATUS "Creating executable 'tests'...")
add_executable(tests tests.cpp ${COMMON_SRCS})

target_include_directories(tests PUBLIC ${CMAKE_SOURCE_DIR})

# Link libraries
target_link_libraries(tests PUBLIC gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)