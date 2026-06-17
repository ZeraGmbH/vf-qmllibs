file(GLOB_RECURSE HEADERS
    *.h
    )

file(GLOB_RECURSE SOURCES
    *.cpp
    )

add_library(pixmap-item
    SHARED
    ${HEADERS}
    ${SOURCES}
    )

target_link_libraries(pixmap-item
    PUBLIC
    ${QTX}::Quick
    ${QTX}::Qml
    ${QTX}::Svg
    )

target_include_directories(pixmap-item
    PUBLIC
    $<INSTALL_INTERFACE:include/pixmap-item>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

set_target_properties(pixmap-item PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(pixmap-item PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS pixmap-item NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS pixmap-item
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pixmap-item
    )

