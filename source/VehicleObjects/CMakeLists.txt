cmake_minimum_required (VERSION 3.2)
project(VehicleObjects)

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

# cpprest directories
include_directories(${CPPREST_INCLUDE_DIR})
link_directories(${CPPREST_LIB_DIR})

# define project's build target with project's source files
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# add macros
add_definitions(-DVEHICLEOBJECTS_EXPORTS)
# add compile options
target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CPPREST_LIB_NAME})