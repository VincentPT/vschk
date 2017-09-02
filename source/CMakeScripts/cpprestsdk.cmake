if(UNIX)
    set (CPPREST_LIB_NAME cpprest)
endif()

set (CPPREST_LIB_NAME_D "")

# cpprest directories
SET (I_CPPRESTSDK_INCLUDE_DIR "")
SET (I_CPPRESTSDK_LIB_DIR "")

# if CPPRESTSDK_INSTALLED_DIR is defined, set include dir and library dir
if (DEFINED CPPRESTSDK_INSTALLED_DIR)
    SET(I_CPPRESTSDK_INCLUDE_DIR ${CPPRESTSDK_INSTALLED_DIR}/include)
    SET(I_CPPRESTSDK_LIB_DIR ${CPPRESTSDK_INSTALLED_DIR}/lib)
endif()

# if WT_INCLUDE_DIR is defined, set include dir
if (DEFINED WT_INCLUDE_DIR)
    SET(I_CPPRESTSDK_INCLUDE_DIR ${WT_INCLUDE_DIR})
endif()

# if WT_LIB_DIR is defined, set library dir
if (DEFINED WT_LIB_DIR)
    SET(I_CPPRESTSDK_LIB_DIR ${WT_LIB_DIR})
endif()

if (MSVC)
    if(${CMAKE_VS_PLATFORM_TOOLSET} STREQUAL "v120")
        set (CPPREST_LIB_NAME "cpprest120_2_9")
        set (CPPREST_LIB_NAME_D "cpprest120d_2_9")
    else()
        set (CPPREST_LIB_NAME_D "cpprest140d_2_9")
        set (CPPREST_LIB_NAME "cpprest140_2_9")
    endif()
        
    if (I_CPPRESTSDK_INCLUDE_DIR STREQUAL "")
        # in case I_CPPRESTSDK_LIB_DIR is not defined, assume that cpprest sdk was install by using nuget
        # and its location is at ./packages
        if(${CMAKE_VS_PLATFORM_TOOLSET} STREQUAL "v140")
            set (I_CPPRESTSDK_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/packages/cpprestsdk.v140.windesktop.msvcstl.dyn.rt-dyn.2.9.1/build/native/include)
        else ()
            set (I_CPPRESTSDK_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/packages/cpprestsdk.v120.windesktop.msvcstl.dyn.rt-dyn.2.9.1/build/native/include)
        endif()
    endif()
    
    if (NOT I_CPPRESTSDK_LIB_DIR STREQUAL "")        
        set (I_CPPRESTSDK_LIB_DIR ${I_CPPRESTSDK_LIB_DIR}/${PLATFORM})
    else ()
        # in case I_CPPRESTSDK_LIB_DIR is not defined, assume that cpprest sdk was install by using nuget
        # and its location is at ./packages
        if(${CMAKE_VS_PLATFORM_TOOLSET} STREQUAL "v140")
            set (I_CPPRESTSDK_LIB_DIR ${CMAKE_SOURCE_DIR}/packages/cpprestsdk.v140.windesktop.msvcstl.dyn.rt-dyn.2.9.1/lib/native/v140/windesktop/msvcstl/dyn/rt-dyn/${PLATFORM})
        else ()
            set (I_CPPRESTSDK_LIB_DIR ${CMAKE_SOURCE_DIR}/packages/cpprestsdk.v120.windesktop.msvcstl.dyn.rt-dyn.2.9.1/lib/native/v120/windesktop/msvcstl/dyn/rt-dyn/${PLATFORM})
        endif()
    endif()
endif()

# apply web toolkit dirs to cmake
if (NOT I_CPPRESTSDK_INCLUDE_DIR STREQUAL "")
    include_directories(${I_CPPRESTSDK_INCLUDE_DIR})
endif ()

if (NOT I_CPPRESTSDK_LIB_DIR STREQUAL "")
    link_directories(${I_CPPRESTSDK_LIB_DIR})
endif()

message(STATUS "cpprest library name:" ${CPPREST_LIB_NAME})
message(STATUS "cpprest include dir:" ${I_CPPRESTSDK_INCLUDE_DIR})
message(STATUS "cpprest library dir:" ${I_CPPRESTSDK_LIB_DIR})