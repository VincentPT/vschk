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

# define project's build target with project's source files
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# add macros
add_definitions(-DVEHICLEOBJECTS_EXPORTS)
target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
target_link_libraries(${PROJECT_NAME} PRIVATE pvt.cppan.demo.microsoft.cpprestsdk-2.9.1)