cmake_minimum_required (VERSION 3.2)
project(VehicleDAO C CXX)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
endif()

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    set (PLATFORM x64)
else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    set (PLATFORM x86)
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

SET(COMMON_SOURCES ../common/IniReader.cpp)
# project's source files
set(SOURCES VehicleDAO.cpp VehicleDAO.h VehicleDAOMacros.h ${COMMON_SOURCES})

# set include directories
include_directories(${PROJECT_SOURCE_DIR}/../)
if (WIN32)
    include_directories(${PROJECT_SOURCE_DIR}/../external/mongo-cxx-driver/include/mongocxx/v_noabi)
    include_directories(${PROJECT_SOURCE_DIR}/../external/mongo-cxx-driver/include/bsoncxx/v_noabi)   
    link_directories(${PROJECT_SOURCE_DIR}/../external/mongo-cxx-driver/lib/${PLATFORM})
else()
    include_directories(/usr/include/bsoncxx/v_noabi)
    include_directories(/usr/include/mongocxx/v_noabi)
endif()

include (boost)

# define project's build target with project's source files
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# add macros
add_definitions(-DVEHICLEDAO_EXPORTS)
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE VehicleObjects)
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE bsoncxx PRIVATE libbsoncxx PRIVATE libmongocxx PRIVATE mongocxx)
else ()
    target_link_libraries(${PROJECT_NAME} PRIVATE bsoncxx PRIVATE mongocxx)
endif ()

if (MSVC)
    SET (INSTALL_DEST ${CMAKE_SOURCE_DIR}/../bin/windows/VehicleServices)
    SET (EXTERNAL_LIB_DIR ${CMAKE_SOURCE_DIR}/external)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Debug/${PROJECT_NAME}.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Release/${PROJECT_NAME}.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
    install(FILES ${EXTERNAL_LIB_DIR}/mongo-c-driver/bin/x64/Debug/libmongoc-1.0.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
    install(FILES ${EXTERNAL_LIB_DIR}/mongo-c-driver/bin/x64/Debug/libbson-1.0.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
    install(FILES ${EXTERNAL_LIB_DIR}/mongo-c-driver/bin/x64/Release/libmongoc-1.0.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
    install(FILES ${EXTERNAL_LIB_DIR}/mongo-c-driver/bin/x64/Release/libbson-1.0.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
    install(FILES ${EXTERNAL_LIB_DIR}/mongo-cxx-driver/bin/x64/Debug/mongocxx.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
    install(FILES ${EXTERNAL_LIB_DIR}/mongo-cxx-driver/bin/x64/Debug/bsoncxx.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
    install(FILES ${EXTERNAL_LIB_DIR}/mongo-cxx-driver/bin/x64/Release/mongocxx.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
    install(FILES ${EXTERNAL_LIB_DIR}/mongo-cxx-driver/bin/x64/Release/bsoncxx.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
endif()