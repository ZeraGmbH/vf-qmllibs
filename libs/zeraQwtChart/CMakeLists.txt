file(GLOB_RECURSE HEADERS
    src/*.h
    )

file(GLOB_RECURSE SOURCES
    src/*.cpp
    )

add_library(qwtcharts
    SHARED
    ${HEADERS}
    ${SOURCES}
    )

target_link_libraries(
    qwtcharts
    PUBLIC
    vector-diagram-lib
    ${QTX}::Quick
    ${QTX}::Qml
    ${QWT_LIBRARIES}
    )

target_include_directories(qwtcharts
    PUBLIC
    $<INSTALL_INTERFACE:include/qwtcharts>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
    ${QWT_INCLUDE_DIRS}
    )

set_target_properties(qwtcharts PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(qwtcharts PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS qwtcharts NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS qwtcharts
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qwtcharts
    )
