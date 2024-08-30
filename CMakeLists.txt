# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10) 

# Name of the project
project(pos-supermarket) 

# Set the C++ standard to use
set(CMAKE_CXX_STANDARD 11) 

# Automatically find all .cpp files in the source directory
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

# Exclude CMake-generated files and directories
list(FILTER SOURCES EXCLUDE REGEX "CMakeFiles")

# Add an executable to the project with all found source files
add_executable(main ${SOURCES})

# Add include directories
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/pos-supermarket)
