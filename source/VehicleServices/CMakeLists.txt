cmake_minimum_required (VERSION 3.2)
project(VehicleServices)

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    SET (PLATFORM x64)
else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    SET (PLATFORM x86)
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

SET(COMMON_SOURCES ../common/IniReader.cpp)

# project's source files
set(SOURCES ${COMMON_SOURCES}
    CrabInterfaces.h
    crab_headers.h
    HttpHandler.cpp
    HttpHandler.h
    RESTResponse.cpp
    RESTResponse.h
    RESTUriParser.cpp
    RESTUriParser.h
    ServiceEngine.cpp
    ServiceEngine.h
    stdafx.h
    VehicleServer.cpp
    web_common.h
    WSVehicleSearch.cpp
    WSVehicleSearch.h
)

# set include directories
include_directories(${PROJECT_SOURCE_DIR}/../)

# cpprest directories
include_directories(${CPPREST_INCLUDE_DIR})
link_directories(${CPPREST_LIB_DIR})

# define project's build target with project's source files
add_executable(${PROJECT_NAME} ${SOURCES})

# add compile options
target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)

target_link_libraries(${PROJECT_NAME} PRIVATE VehicleObjects)
target_link_libraries(${PROJECT_NAME} PRIVATE VehicleDAO)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CPPREST_LIB_NAME})