# FindGMock.cmake
# Locate GoogleMock library and include directories

find_package(GTest REQUIRED)

if (NOT GTEST_FOUND)
  message(FATAL_ERROR "GoogleTest not found.")
endif()

find_path(GMOCK_INCLUDE_DIR
  NAMES gmock/gmock.h
  PATHS ${CMAKE_INSTALL_PREFIX}/include
  PATH_SUFFIXES gmock
)

find_library(GMOCK_LIBRARY
  NAMES gmock
  PATHS ${CMAKE_INSTALL_PREFIX}/lib
)

find_library(GMOCK_MAIN_LIBRARY
  NAMES gmock_main
  PATHS ${CMAKE_INSTALL_PREFIX}/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GMock DEFAULT_MSG GMOCK_LIBRARY GMOCK_INCLUDE_DIR)

if (GMOCK_FOUND)
  add_library(GMock::gmock STATIC IMPORTED)
  set_target_properties(GMock::gmock PROPERTIES
    IMPORTED_LOCATION ${GMOCK_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${GMOCK_INCLUDE_DIR}
  )

  add_library(GMock::gmock_main STATIC IMPORTED)
  set_target_properties(GMock::gmock_main PROPERTIES
    IMPORTED_LOCATION ${GMOCK_MAIN_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${GMOCK_INCLUDE_DIR}
  )
endif()

mark_as_advanced(GMOCK_INCLUDE_DIR GMOCK_LIBRARY GMOCK_MAIN_LIBRARY)
