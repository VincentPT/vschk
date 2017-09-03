cmake_minimum_required (VERSION 3.2)
project(VehicleServicesUT C CXX)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
endif()

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    SET (PLATFORM x64)
else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    SET (PLATFORM x86)
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

# project's source files
set(SOURCES
    ../VehicleServices/HttpHandler.cpp
    ../VehicleServices/RESTUriParser.cpp
    ../VehicleServices/ServiceEngine.cpp
    RESTUriParserUT.cpp
    ServiceEngineUT.cpp
    VehicleServiceUT.cpp
    VehicleServicesUTMacros.h
)

# set include directories
include_directories(${PROJECT_SOURCE_DIR}/../)
include_directories(${PROJECT_SOURCE_DIR}/../VehicleServices)
include_directories(${PROJECT_SOURCE_DIR}/../external/catch/include)
include(cpprestsdk)

# define project's build target with project's source files
add_executable(${PROJECT_NAME} ${SOURCES})

# add compile options
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif ()

if (NOT ${CPPREST_LIB_NAME_D} STREQUAL "")
    target_link_libraries(${PROJECT_NAME} PRIVATE  debug ${CPPREST_LIB_NAME_D})
    target_link_libraries(${PROJECT_NAME} PRIVATE optimized ${CPPREST_LIB_NAME})
else ()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CPPREST_LIB_NAME})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE VehicleObjects)
target_link_libraries(${PROJECT_NAME} PRIVATE VehicleDAO)

if(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE boost_system)
    target_link_libraries(${PROJECT_NAME} PRIVATE crypto)
    target_link_libraries(${PROJECT_NAME} PRIVATE ssl)
endif()

if (MSVC)
    SET (INSTALL_DEST ${CMAKE_SOURCE_DIR}/../bin/windows/VehicleServices)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Debug/${PROJECT_NAME}.exe DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Release/${PROJECT_NAME}.exe DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
endif()