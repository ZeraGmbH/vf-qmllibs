file(GLOB_RECURSE HEADERS
    *.h
    )

file(GLOB_RECURSE SOURCES
    *.cpp
    )

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_subdirectory("qml")
else()
    qtquick_compiler_add_resources(RESOURCES anmlib.qrc)
endif()

add_library(anmlib
    SHARED
    ${HEADERS}
    ${SOURCES}
    ${RESOURCES}
    )

SET_QML_PATH(anmlib qml)

target_link_libraries(anmlib
    PUBLIC
    ${QTX}::Quick
    ${QTX}::Qml
    ${QTX}::DBus
    ${KFX}::NetworkManagerQt
    ${KFX}::ModemManagerQt
    ZeraTranslation::ZeraTranslation
    SortFilterProxyModel::SortFilterProxyModel
    FontAweSomeQml::FontAweSomeQml
    zerafa
    zeracomponents
    qmlhelpers
    )

target_include_directories(anmlib
    PUBLIC
    $<INSTALL_INTERFACE:include/anmlib>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/connection-settings>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ConnectionTree>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/networks>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cppNotificationHandler>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/devices>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/info>
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

