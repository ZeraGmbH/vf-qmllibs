add_library(zerafa
    SHARED
    zerafa.h
    zerafa.cpp
    zerafa.qrc
    )

target_link_libraries(
    zerafa
    PUBLIC
    Qt5::Quick
    Qt5::Qml
    )

target_include_directories(zerafa
    PUBLIC
    $<INSTALL_INTERFACE:include/zerafa>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

set_target_properties(zerafa PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zerafa PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS zerafa NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS zerafa
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zerafa
    )

