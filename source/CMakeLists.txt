cmake_minimum_required (VERSION 3.0)

project (vschk)
# The version number.
set (MKOCR_VERSION_MAJOR 1)
set (MKOCR_VERSION_MINOR 0)

if( CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET (PLATFORM x64)
else( CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET (PLATFORM x86)
endif( CMAKE_SIZEOF_VOID_P EQUAL 8)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/vschk-config.h.in"
    "${PROJECT_BINARY_DIR}/vschk-config.h"
  )

# find dependency libraries for whole solution base on installed nuget packages
# or you can specify them by cmake command line with -D option
message(STATUS "the current tool set is:" ${CMAKE_VS_PLATFORM_TOOLSET})

set (CPPREST_LIB_NAME "cpprest140_2_9" CACHE STRING "")
set (LIBRARIES_DIR ${CMAKE_SOURCE_DIR}/packages)

if(MSVC)
    if(${CMAKE_VS_PLATFORM_TOOLSET} EQUAL "v120")    
        set (CPPREST_LIB_NAME "cpprest120_2_9" CACHE STRING "")
    else()
        set (CPPREST_LIB_NAME "cpprest140_2_9" CACHE STRING "")
    endif()
endif()

message(STATUS "cpprest name:" ${CPPREST_LIB_NAME})

if(DEFINED ${CPPREST_DIR})
    set(CPPREST_INCLUDE_DIR ${CPPREST_DIR}/include CACHE PATH "")    
    set(CPPREST_LIB_DIR ${CPPREST_DIR}/lib CACHE PATH "")    
endif()

if(NOT DEFINED ${CPPREST_INCLUDE_DIR})
    set(CPPREST_INCLUDE_DIR ${LIBRARIES_DIR}/cpprestsdk.v140.windesktop.msvcstl.dyn.rt-dyn.2.9.1/build/native/include CACHE PATH "")    
endif()

if(NOT DEFINED ${CPPREST_LIB_DIR})    
    set(CPPREST_LIB_DIR ${LIBRARIES_DIR}/cpprestsdk.v140.windesktop.msvcstl.dyn.rt-dyn.2.9.1/lib/native/v140/windesktop/msvcstl/dyn/rt-dyn/${PLATFORM} CACHE PATH "")
endif()

if(NOT DEFINED ${BOOST_INCLUDE_DIR})
    set(BOOST_INCLUDE_DIR ${LIBRARIES_DIR}/boost.1.64.0.0/lib/native/include CACHE PATH "")    
endif()

message(STATUS "cpprest include dir:" ${CPPREST_INCLUDE_DIR})
message(STATUS "cpprest lib dir:" ${CPPREST_LIB_DIR})

# add_subdirectory(.cppan)
add_subdirectory(VehicleDAO)
add_subdirectory(VehicleObjects)
add_subdirectory(VehicleServices)
add_subdirectory(VehicleWebApp)