cmake_minimum_required (VERSION 3.0)

project (vschk)

if (MSVC)
    set (CMAKE_CONFIGURATION_TYPES Debug;Release)
endif()

# The version number.
set (MKOCR_VERSION_MAJOR 1)
set (MKOCR_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/vschk-config.h.in"
    "${PROJECT_BINARY_DIR}/vschk-config.h"
  )

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeScripts)
  
add_subdirectory(VehicleObjects)
add_subdirectory(VehicleDAO)
add_subdirectory(VehicleServices)
add_subdirectory(VehicleWebApp)
add_subdirectory(VehicleServicesUT)