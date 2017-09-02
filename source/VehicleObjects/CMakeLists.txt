cmake_minimum_required (VERSION 3.2)
project(VehicleObjects)

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
    Jsonable.cpp
    Jsonable.h
    JsonObject.cpp
    JsonObject.h
    StolenVehicleInfo.cpp
    StolenVehicleInfo.h
    VehicleObjectsMacros.h
    VehicleOwner.cpp
    VehicleOwner.h
)

message(STATUS "cmake module path:" ${CMAKE_MODULE_PATH})

include(cpprestsdk)

# define project's build target with project's source files
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# add macros
add_definitions(-DVEHICLEOBJECTS_EXPORTS)
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

if (MSVC)
    SET (INSTALL_DEST ${CMAKE_SOURCE_DIR}/../bin/windows/VehicleServices)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Debug/${PROJECT_NAME}.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Release/${PROJECT_NAME}.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
endif()