# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Name of the project
project(pos-supermarket)

# Set the C++ standard to use
set(CMAKE_CXX_STANDARD 11)

# Set default build type to Release if not provided
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

# Set compiler flags for Debug and Release modes
set(CMAKE_CXX_FLAGS_DEBUG "-g -fprofile-arcs -ftest-coverage")  # Debug symbols + coverage flags
set(CMAKE_CXX_FLAGS_RELEASE "-O3")    # Optimization for Release

# Automatically find all .cpp files in the src directory
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Exclude CMake-generated files and directories
list(FILTER SOURCES EXCLUDE REGEX "CMakeFiles")

# Add an executable to the project with all found source files
add_executable(pos-supermarket ${SOURCES})

# Add include directories
target_include_directories(pos-supermarket PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Add the SQLiteCpp library from the submodule
add_subdirectory(external/SQLiteCpp)

# Link it with your target
target_link_libraries(pos-supermarket SQLiteCpp)

# Include the tests directory for the testing setup
add_subdirectory(tests)

# Enable testing procedures
enable_testing()
