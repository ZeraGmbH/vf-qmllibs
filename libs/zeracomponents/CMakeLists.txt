file(GLOB_RECURSE HEADERS
    src/*.h
    )

file(GLOB_RECURSE SOURCES
    src/*.cpp
    )

add_library(zeracomponents
    SHARED
    ${HEADERS}
    ${SOURCES}
    zeracomponents.qrc
    )

target_link_libraries(
    zeracomponents
    PUBLIC
    qmlhelpers
    )

target_include_directories(zeracomponents
    PUBLIC
    $<INSTALL_INTERFACE:include/zeracomponents>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    )

set_target_properties(zeracomponents PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zeracomponents PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS zeracomponents NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS zeracomponents
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zeracomponents
    )

