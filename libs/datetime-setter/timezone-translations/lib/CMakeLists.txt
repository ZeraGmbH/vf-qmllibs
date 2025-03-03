file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cpp)

add_library(timezone-translations SHARED
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(timezone-translations
    PUBLIC
    Qt5::Core
)

target_include_directories(timezone-translations
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/timezone-translations>
)

set_target_properties(timezone-translations PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(timezone-translations PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS timezone-translations NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS timezone-translations
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/timezone-translations
    )
