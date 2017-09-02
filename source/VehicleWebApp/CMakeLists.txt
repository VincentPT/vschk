cmake_minimum_required (VERSION 3.2)

project(VehicleWebApp C CXX)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
endif()

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
include (webtoolkit)
include (cpprestsdk)

# define project's build target with project's source files
add_executable(${PROJECT_NAME} ${SOURCES})

if(MSVC)
    # add compile options
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)

    # add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${WT_INSTALLED_DIR}/bin/wt.dll ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))
    # add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${WT_INSTALLED_DIR}/bin/wtdbo.dll ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))
    # add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${WT_INSTALLED_DIR}/bin/wthttp.dll ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))
endif(MSVC)

if (NOT I_CPPRESTSDK_LIB_DIR STREQUAL "")
    target_link_libraries(${PROJECT_NAME}
        PRIVATE optimized wt
        PRIVATE optimized wtdbo
        PRIVATE optimized wthttp
        PRIVATE debug wtd
        PRIVATE debug wtdbod
        PRIVATE debug wthttpd
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE  debug ${CPPREST_LIB_NAME_D})
    target_link_libraries(${PROJECT_NAME} PRIVATE optimized ${CPPREST_LIB_NAME})    
else ()
    target_link_libraries(${PROJECT_NAME}
        PRIVATE wt
        PRIVATE wtdbo
        PRIVATE wthttp
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CPPREST_LIB_NAME})
endif()

if(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE boost_system)
    target_link_libraries(${PROJECT_NAME} PRIVATE crypto)
    target_link_libraries(${PROJECT_NAME} PRIVATE ssl)
endif()

if (MSVC)
    SET (INSTALL_DEST ${CMAKE_SOURCE_DIR}/../bin/windows/VehicleWebApp)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Debug/${PROJECT_NAME}.exe DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Release/${PROJECT_NAME}.exe DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
    install(FILES ${PROJECT_SOURCE_DIR}/app.ini DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug|Release)
    install(FILES ${PROJECT_SOURCE_DIR}/run-web-app.bat DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug|Release)
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/docroot DESTINATION ${CMAKE_SOURCE_DIR}/../bin CONFIGURATIONS Debug|Release)
    
    if (NOT ${CPPREST_LIB_NAME_D} STREQUAL "")
        install(FILES ${I_CPPRESTSDK_LIB_DIR}/Debug/${CPPREST_LIB_NAME_D}.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
        install(FILES ${I_CPPRESTSDK_LIB_DIR}/Release/${CPPREST_LIB_NAME}.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
    else ()
        install(FILES ${I_CPPRESTSDK_LIB_DIR}/Release/${CPPREST_LIB_NAME}.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug|Release)
    endif()
    
    if (DEFINED WT_INSTALLED_DIR)
        install(FILES ${WT_INSTALLED_DIR}/bin/libeay32.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
        install(FILES ${WT_INSTALLED_DIR}/bin/libeay32d.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
        install(FILES ${WT_INSTALLED_DIR}/bin/libhpdf.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
        install(FILES ${WT_INSTALLED_DIR}/bin/libhpdfd.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
        install(FILES ${WT_INSTALLED_DIR}/bin/libmariadb.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
        install(FILES ${WT_INSTALLED_DIR}/bin/libmariadbd.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
        install(FILES ${WT_INSTALLED_DIR}/bin/libpng14.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
        install(FILES ${WT_INSTALLED_DIR}/bin/libpng14d.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
        install(FILES ${WT_INSTALLED_DIR}/bin/ssleay32.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
        install(FILES ${WT_INSTALLED_DIR}/bin/ssleay32d.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
        install(FILES ${WT_INSTALLED_DIR}/bin/wt.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
        install(FILES ${WT_INSTALLED_DIR}/bin/wtd.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
        install(FILES ${WT_INSTALLED_DIR}/bin/wtdbo.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
        install(FILES ${WT_INSTALLED_DIR}/bin/wtdbod.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
        install(FILES ${WT_INSTALLED_DIR}/bin/wtdbofirebird.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
        install(FILES ${WT_INSTALLED_DIR}/bin/wtdbofirebirdd.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
        install(FILES ${WT_INSTALLED_DIR}/bin/wtdbomysql.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
        install(FILES ${WT_INSTALLED_DIR}/bin/wtdbomysqld.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
        install(FILES ${WT_INSTALLED_DIR}/bin/wtdbopostgres.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
        install(FILES ${WT_INSTALLED_DIR}/bin/wtdbopostgresd.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
        install(FILES ${WT_INSTALLED_DIR}/bin/wtdbosqlite3.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
        install(FILES ${WT_INSTALLED_DIR}/bin/wtdbosqlite3d.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
        install(FILES ${WT_INSTALLED_DIR}/bin/wthttp.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
        install(FILES ${WT_INSTALLED_DIR}/bin/wthttpd.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
        install(FILES ${WT_INSTALLED_DIR}/bin/zlib.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Release)
        install(FILES ${WT_INSTALLED_DIR}/bin/zlibd.dll DESTINATION ${INSTALL_DEST} CONFIGURATIONS Debug)
    endif()
endif()