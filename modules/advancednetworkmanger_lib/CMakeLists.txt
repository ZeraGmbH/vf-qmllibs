file(GLOB_RECURSE APP_HEADERS
    src/*.h
    )

file(GLOB_RECURSE APP_SOURCES
    src/*.cpp
    )

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    qt5_add_resources(PLUGIN_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/anmlib.qrc)
else()
    qtquick_compiler_add_resources(PLUGIN_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/anmlib.qrc)
endif()

add_library(anmlib
    SHARED
    ${APP_HEADERS}
    ${APP_SOURCES}
    ${PLUGIN_RESOURCES}     # Plugin resources file
    )

target_link_libraries(
    anmlib
    PUBLIC
    Qt5::Core
    Qt5::Quick
    Qt5::Qml
    Qt5::DBus
    KF5::NetworkManagerQt
    KF5::ModemManagerQt
    ZeraTranslation::ZeraTranslation
    ZeraQml::SortFilterProxyModelCmake
    zerafa
    )

target_include_directories(anmlib
    PUBLIC
    $<INSTALL_INTERFACE:include/anmlib>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ConnectionTree>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ConnectionTypes>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/cppNotificationHandler>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/devices>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/info>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/PropertieInterfaces>
    )

set_target_properties(anmlib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(anmlib PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

include(GenerateExportHeader)
generate_export_header(anmlib)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/anmlib_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/anmlib
    )

install(TARGETS anmlib
    EXPORT anmlibExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    anmlibConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMinorVersion
    )

configure_file(anmlibConfig.cmake.in anmlibConfig.cmake @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/anmlibConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/anmlibConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/anmlib
    )

install(EXPORT anmlibExport
    FILE anmlibTargets.cmake
    NAMESPACE ZeraQml::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/anmlib
    )

install(
    FILES ${APP_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/anmlib
    )
