add_custom_target( # for visibility in qt creator
    timedate1-dbus-xml
    SOURCES timedate1.xml timedate1.readme
)

qt5_add_dbus_interface(INTERFACE_SOURCES timedate1.xml timedate1interface)

file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cpp)

add_library(timedate1-interface SHARED
    ${INTERFACE_SOURCES}
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(timedate1-interface
    PUBLIC
    Zera::zera-timers
    Qt5::DBus
    timezone-translations
)

target_include_directories(timedate1-interface
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

set_target_properties(timedate1-interface PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(timedate1-interface PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS timedate1-interface NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS timedate1-interface
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/timedate1-interface
    )
