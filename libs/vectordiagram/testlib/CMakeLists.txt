file(GLOB SOURCES
    *.cpp
    )

file(GLOB HEADER
    *.h
    )

add_library(vector-diagram-testlib STATIC
    ${SOURCES}
    ${HEADER}
)

target_include_directories(vector-diagram-testlib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/vector-diagram-testlib>
    )

add_definitions(-DOE_INSTALL_ROOT="${OE_INSTALL_ROOT}")

target_link_libraries(vector-diagram-testlib
    PUBLIC
    vector-diagram-lib
)

set_target_properties(vector-diagram-testlib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(vector-diagram-testlib PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS vector-diagram-testlib NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS vector-diagram-testlib
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/vector-diagram-testlib
    )
