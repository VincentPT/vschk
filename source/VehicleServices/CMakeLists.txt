cmake_minimum_required (VERSION 3.2)
project(VehicleServices)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
endif()

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

include(cpprestsdk)

# define project's build target with project's source files
add_executable(${PROJECT_NAME} ${SOURCES})

# add compile options
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE VehicleObjects)
target_link_libraries(${PROJECT_NAME} PRIVATE VehicleDAO)

if (NOT ${CPPREST_LIB_NAME_D} STREQUAL "")
    target_link_libraries(${PROJECT_NAME} PRIVATE  debug ${CPPREST_LIB_NAME_D})
    target_link_libraries(${PROJECT_NAME} PRIVATE optimized ${CPPREST_LIB_NAME})
else ()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CPPREST_LIB_NAME})
endif()

if(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE boost_system)
    target_link_libraries(${PROJECT_NAME} PRIVATE crypto)
    target_link_libraries(${PROJECT_NAME} PRIVATE ssl)
endif()

if (MSVC)
    SET (INSTALL_DEST ${CMAKE_SOURCE_DIR}/../bin/windows/VehicleServices)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Debug/${PROJECT_NAME}.exe DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Release/${PROJECT_NAME}.exe DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
    install(FILES ${PROJECT_SOURCE_DIR}/app.ini DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug|Release)
    
    if (NOT ${CPPREST_LIB_NAME_D} STREQUAL "")
        install(FILES ${I_CPPRESTSDK_LIB_DIR}/Debug/${CPPREST_LIB_NAME_D}.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
        install(FILES ${I_CPPRESTSDK_LIB_DIR}/Release/${CPPREST_LIB_NAME}.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
    else ()
        install(FILES ${I_CPPRESTSDK_LIB_DIR}/Release/${CPPREST_LIB_NAME}.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug|Release)
    endif()
endif()