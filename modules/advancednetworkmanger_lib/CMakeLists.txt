file(GLOB_RECURSE HEADERS
    src/*.h
    )

file(GLOB_RECURSE SOURCES
    src/*.cpp
    )

add_library(anmlib
    SHARED
    ${HEADERS}
    ${SOURCES}
    anmlib.qrc
    )

target_link_libraries(
    anmlib
    PUBLIC
    Qt5::Quick
    Qt5::Qml
    Qt5::DBus
    KF5::NetworkManagerQt
    KF5::ModemManagerQt
    ZeraTranslation::ZeraTranslation
    ZeraQml::SortFilterProxyModelCmake
    zerafa
    zeracomponents
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

export(TARGETS anmlib NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS anmlib
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/anmlib
    )
