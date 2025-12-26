file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cpp)

add_library(timedate-qml-wrapper SHARED
    ${INTERFACE_SOURCES}
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(timedate-qml-wrapper
    PUBLIC
    ${QTX}::Qml
    timedate1-interface
)

target_include_directories(timedate-qml-wrapper
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/timedate-qml-wrapper>
)

set_target_properties(timedate-qml-wrapper PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(timedate-qml-wrapper PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS timedate-qml-wrapper NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS timedate-qml-wrapper
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/timedate-qml-wrapper
    )
