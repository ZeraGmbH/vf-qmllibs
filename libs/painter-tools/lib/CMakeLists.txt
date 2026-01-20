file(GLOB_RECURSE HEADERS
    *.h
    )

file(GLOB_RECURSE SOURCES
    *.cpp
    )

add_library(painter-tools
    SHARED
    ${HEADERS}
    ${SOURCES}
    )

target_link_libraries(painter-tools
    PUBLIC
    ${QTX}::Gui
    )

target_include_directories(painter-tools
    PUBLIC
    $<INSTALL_INTERFACE:include/painter-tools>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

set_target_properties(painter-tools PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(painter-tools PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS painter-tools NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS painter-tools
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/painter-tools
    )

