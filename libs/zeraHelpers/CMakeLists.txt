file(GLOB_RECURSE HEADERS
    *.h
    )

file(GLOB_RECURSE SOURCES
    *.cpp
    )

add_library(qmlhelpers
    SHARED
    ${HEADERS}
    ${SOURCES}
    qmlhelpers.qrc
    )

SET_QML_PATH(qmlhelpers qml)

target_link_libraries(qmlhelpers
    PUBLIC
    Qt5::Quick
    )

target_include_directories(qmlhelpers
    PUBLIC
    $<INSTALL_INTERFACE:include/qmlhelpers>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

set_target_properties(qmlhelpers PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(qmlhelpers PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS qmlhelpers NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS qmlhelpers
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qmlhelpers
    )

