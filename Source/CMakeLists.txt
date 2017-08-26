cmake_minimum_required (VERSION 3.0)
project (vschk)
# The version number.
set (MKOCR_VERSION_MAJOR 1)
set (MKOCR_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/vschk-config.h.in"
    "${PROJECT_BINARY_DIR}/vschk-config.h"
  )

add_subdirectory(.cppan)
add_subdirectory(VehicleDAO)
add_subdirectory(VehicleObjects)