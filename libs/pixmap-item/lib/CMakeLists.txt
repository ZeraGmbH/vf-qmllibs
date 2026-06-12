file(GLOB_RECURSE HEADERS
    *.h
    )

file(GLOB_RECURSE SOURCES
    *.cpp
    )

add_library(pixman-item
    SHARED
    ${HEADERS}
    ${SOURCES}
    )

target_link_libraries(pixman-item
    PUBLIC
    ${QTX}::Quick
    ${QTX}::Qml
    )

target_include_directories(pixman-item
    PUBLIC
    $<INSTALL_INTERFACE:include/pixman-item>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

set_target_properties(pixman-item PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(pixman-item PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS pixman-item NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS pixman-item
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pixman-item
    )

