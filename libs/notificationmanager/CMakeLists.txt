project(notificationmanager VERSION 1.0 LANGUAGES CXX C)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message(STATUS "Debug type: " ${CMAKE_BUILD_TYPE})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -O0 -g")
endif()

set(CMAKE_AUTOMOC ON)

set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "1")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

file(GLOB_RECURSE APP_HEADERS
    lib/*.h
    )

file(GLOB_RECURSE APP_SOURCES
    lib/*.cpp
    )

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    qt5_add_resources(PLUGIN_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/notificationmanager.qrc)
else()
    qtquick_compiler_add_resources(PLUGIN_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/notificationmanager.qrc)
endif()

add_library(
    notificationmanager
    SHARED
    ${APP_HEADERS}
    ${APP_SOURCES}
    ${PLUGIN_RESOURCES}
    )

target_link_libraries(
    notificationmanager
    PUBLIC
    Qt5::Core
    Qt5::Quick
    )

target_include_directories(notificationmanager
    PUBLIC
    $<INSTALL_INTERFACE:include/notificationmanager>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

set_target_properties(notificationmanager PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(notificationmanager PROPERTIES SOVERSION ${notificationmanager_VERSION_MAJOR})

include(GenerateExportHeader)
generate_export_header(notificationmanager)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/notificationmanager_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/notificationmanager
    )

install(TARGETS notificationmanager
    EXPORT notificationmanagerExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    notificationmanagerConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMinorVersion
    )

configure_file(notificationmanagerConfig.cmake.in notificationmanagerConfig.cmake @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/notificationmanagerConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/notificationmanagerConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/notificationmanager
    )


install(TARGETS notificationmanager
    EXPORT notificationmanager
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )


install(EXPORT notificationmanagerExport
    FILE notificationmanagerTargets.cmake
    NAMESPACE ZeraQml::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/notificationmanager
    )

install(
    FILES ${APP_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/notificationmanager
    )
