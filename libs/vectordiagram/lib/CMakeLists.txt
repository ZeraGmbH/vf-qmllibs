file(GLOB_RECURSE HEADERS
    *.h
    )

file(GLOB_RECURSE SOURCES
    *.cpp
    )

add_library(vector-diagram-lib
    SHARED
    ${HEADERS}
    ${SOURCES}
    )

target_link_libraries(vector-diagram-lib
    PUBLIC
    ${QTX}::Quick
    ${QTX}::Qml
    ${QTX}::Svg
    Zera::zera-timers
    )

target_include_directories(vector-diagram-lib
    PUBLIC
    $<INSTALL_INTERFACE:include/vector-diagram-lib>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/paintworkers>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/qml>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/settings>
    )

set_target_properties(vector-diagram-lib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(vector-diagram-lib PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS vector-diagram-lib NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS vector-diagram-lib
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/vector-diagram-lib
    )

