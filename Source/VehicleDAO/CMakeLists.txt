cmake_minimum_required (VERSION 3.2)
project(VehicleDAO)

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    SET (PLATFORM x64)
else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    SET (PLATFORM x86)
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

SET(COMMON_SOURCES ../common/IniReader.cpp)
# project's source files
set(SOURCES VehicleDAO.cpp VehicleDAO.h VehicleDAOMacros.h ${COMMON_SOURCES})

# set include directories
include_directories(${PROJECT_SOURCE_DIR}/../)
include_directories(${PROJECT_SOURCE_DIR}/../external/mongo-cxx-driver/include/mongocxx/v_noabi)
include_directories(${PROJECT_SOURCE_DIR}/../external/mongo-cxx-driver/include/bsoncxx/v_noabi)

# set link directories (must call before add_library, add_executable)
link_directories(${PROJECT_SOURCE_DIR}/../external/mongo-cxx-driver/lib/${PLATFORM})

# define project's build target with project's source files
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# add macros
add_definitions(-DVEHICLEDAO_EXPORTS)
target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)

target_link_libraries(${PROJECT_NAME} PRIVATE VehicleObjects)
target_link_libraries(${PROJECT_NAME} PRIVATE pvt.cppan.demo.boost.optional-1.64.0)
target_link_libraries(${PROJECT_NAME} PRIVATE pvt.cppan.demo.boost.smart_ptr-1.64.0)
target_link_libraries(${PROJECT_NAME} PRIVATE pvt.cppan.demo.boost.utility-1.64.0)
target_link_libraries(${PROJECT_NAME} PRIVATE bsoncxx PRIVATE libbsoncxx PRIVATE libmongocxx PRIVATE mongocxx)