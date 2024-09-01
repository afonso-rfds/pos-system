# Locate GTest and GMock
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

# Include directories for GTest and GMock
include_directories(${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS})

# Automatically find all .cpp files in the pos-supermarket directory (shared code)
file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/pos-supermarket/*.cpp")

# Automatically find all .cpp files in the tests directory
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Exclude main.cpp from PROJECT_SOURCES to avoid conflicts with GoogleTest's main
list(FILTER PROJECT_SOURCES EXCLUDE REGEX ".*main.cpp$")

# Add an executable for the tests (only including necessary files)
add_executable(run_tests ${PROJECT_SOURCES} ${TEST_SOURCES})

# Link the GoogleTest and GoogleMock libraries, and pthread
target_link_libraries(run_tests
  PRIVATE GTest::gtest_main  # Use gtest_main for GoogleTest's main function
  PRIVATE GMock::gmock      # Link GoogleMock
  PRIVATE GMock::gmock_main # Link GoogleMock main
  PRIVATE pthread
)

# Add include directories for the test executable
target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/pos-supermarket)
