# Add the GoogleTest subdirectory (source directory and binary directory)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/googletest ${CMAKE_BINARY_DIR}/googletest)

# Automatically find all .cpp files in the pos-supermarket directory (shared code)
file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/pos-supermarket/*.cpp")

# Automatically find all .cpp files in the tests directory
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Exclude main.cpp from PROJECT_SOURCES to avoid conflicts with GoogleTest's main
list(FILTER PROJECT_SOURCES EXCLUDE REGEX ".*main.cpp$")

# Add an executable for the tests (only including necessary files)
add_executable(run_tests ${PROJECT_SOURCES} ${TEST_SOURCES})

# Link the GoogleTest, GoogleMock, SQLiteCpp libraries, and pthread
target_link_libraries(run_tests
  PRIVATE gtest          # Link GoogleTest from the submodule
  PRIVATE gtest_main     # Use GoogleTest's main function from submodule
  PRIVATE gmock          # Link GoogleMock from submodule
  PRIVATE gmock_main     # Use GoogleMock's main function from submodule
  PRIVATE SQLiteCpp      # Link SQLiteCpp
  PRIVATE pthread
)

# Add include directories for the test executable
target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/pos-supermarket)
