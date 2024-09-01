# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Name of the project
project(pos-supermarket)

# Set the C++ standard to use
set(CMAKE_CXX_STANDARD 11)

# Include the directory where custom CMake modules are located
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/tests/cmake ${CMAKE_MODULE_PATH})

# Automatically find all .cpp files in the root directory
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/pos-supermarket/*.cpp")

# Exclude CMake-generated files and directories
list(FILTER SOURCES EXCLUDE REGEX "CMakeFiles")

# Add an executable to the project with all found source files
add_executable(main ${SOURCES})

# Add include directories
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/pos-supermarket)

# Include the tests directory for the testing setup
add_subdirectory(tests)

# Enable testing procedures
enable_testing()
