cmake_minimum_required (VERSION 3.2)

project(VehicleWebApp)

if( CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET (PLATFORM x64)
else( CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET (PLATFORM x86)
endif( CMAKE_SIZEOF_VOID_P EQUAL 8)

SET(COMMON_SOURCES ../common/IniReader.cpp)

# project's source files
set(SOURCES ${COMMON_SOURCES}
    HttpRequester.cpp
    HttpRequester.h
    JsonObject.cpp
    JsonObject.h
    main.cpp
    RESTResponse.cpp
    RESTResponse.h
    StolenVehicleInfo.cpp
    StolenVehicleInfo.h
    VehicleOwner.cpp
    VehicleOwner.h
    WebAppMacros.h
)

# set include directories
include_directories(${PROJECT_SOURCE_DIR}/../)

# web toolkit root directory must be intialize through command line using -DWT_INSTALLED_DIR=/your/cdriver/prefix
# just make sure that you set a corresponding web toolkit directory with your platform you build (x86 or x64) 
include_directories(${WT_INSTALLED_DIR}/include)
link_directories(${WT_INSTALLED_DIR}/lib)

# cpprest directories
include_directories(${CPPREST_INCLUDE_DIR})
link_directories(${CPPREST_LIB_DIR})

# define project's build target with project's source files
add_executable(${PROJECT_NAME} ${SOURCES})

# add compile options
target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)

if(MSVC)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${WT_INSTALLED_DIR}/bin/wt.dll ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${WT_INSTALLED_DIR}/bin/wtdbo.dll ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${WT_INSTALLED_DIR}/bin/wthttp.dll ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))
endif(MSVC)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CPPREST_LIB_NAME})
target_link_libraries(${PROJECT_NAME}
    PRIVATE wt
    PRIVATE wtdbo
    PRIVATE wthttp
)