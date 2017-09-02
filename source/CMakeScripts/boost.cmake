# cpprest directories
SET (I_BOOST_INCLUDE_DIR "")

# if BOOST_INSTALLED_DIR is defined, set include dir and library dir
if (DEFINED BOOST_INSTALLED_DIR)
    SET(I_BOOST_INCLUDE_DIR ${BOOST_INSTALLED_DIR}/include)
endif()

# if WT_INCLUDE_DIR is defined, set include dir
if (DEFINED BOOST_INSTALLED_DIR)
    SET(I_BOOST_INCLUDE_DIR ${BOOST_INSTALLED_DIR})
endif()

if (MSVC)
    if (I_BOOST_INCLUDE_DIR STREQUAL "")
        # in case I_BOOST_LIB_DIR is not defined, assume that boost was installed by using nuget
        # and its location is at ./packages
        set (I_BOOST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/packages/boost.1.64.0.0/lib/native/include)
    endif()    
endif()

# apply web toolkit dirs to cmake
if (NOT I_BOOST_INCLUDE_DIR STREQUAL "")
    include_directories(${I_BOOST_INCLUDE_DIR})
endif ()

message(STATUS "boost include dir:" ${I_BOOST_INCLUDE_DIR})