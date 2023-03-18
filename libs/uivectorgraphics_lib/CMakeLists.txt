file(GLOB_RECURSE HEADERS
    src/*.h
    )

file(GLOB_RECURSE SOURCES
    src/*.cpp
    )

add_library(uivlib
    SHARED
    ${HEADERS}
    ${SOURCES}
    uivlib.qrc
    )

target_link_libraries(
    uivlib
    PUBLIC
    Qt5::Quick
    Qt5::Qml
    )

target_include_directories(uivlib
    PUBLIC
    $<INSTALL_INTERFACE:include/uivlib>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    )

set_target_properties(uivlib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(uivlib PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS uivlib NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS uivlib
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/uivlib
    )

