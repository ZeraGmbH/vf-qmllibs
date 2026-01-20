file(GLOB_RECURSE HEADERS
    *.h
    )

file(GLOB_RECURSE SOURCES
    *.cpp
    )

add_library(line-charts-qt
    SHARED
    ${HEADERS}
    ${SOURCES}
    )

target_link_libraries(line-charts-qt
    PUBLIC
    ${QTX}::Charts
    ${QTX}::Widgets
    ${QTX}::Quick
    ${QTX}::Qml
    )

target_include_directories(line-charts-qt
    PUBLIC
    $<INSTALL_INTERFACE:include/line-charts-qt>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

set_target_properties(line-charts-qt PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(line-charts-qt PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS line-charts-qt NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS line-charts-qt
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/line-charts-qt
    )

