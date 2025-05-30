file(GLOB_RECURSE HEADERS
    src/*.h
    )

file(GLOB_RECURSE SOURCES
    src/*.cpp
    )

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_subdirectory("src/qml")
else()
    qtquick_compiler_add_resources(RESOURCES anmlib.qrc)
endif()

add_library(anmlib
    SHARED
    ${HEADERS}
    ${SOURCES}
    ${RESOURCES}
    )

SET_QML_PATH(anmlib src/qml)

target_link_libraries(anmlib
    PUBLIC
    Qt5::Quick
    Qt5::Qml
    Qt5::DBus
    KF5::NetworkManagerQt
    KF5::ModemManagerQt
    ZeraTranslation::ZeraTranslation
    FontAweSomeQml::FontAweSomeQml
    zerafa
    zeracomponents
    qmlhelpers
    )

target_include_directories(anmlib
    PUBLIC
    $<INSTALL_INTERFACE:include/anmlib>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/connection-settings>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ConnectionTree>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/networks>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/cppNotificationHandler>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/devices>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/info>
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
