file(GLOB_RECURSE HEADERS
    *.h
    )

file(GLOB_RECURSE SOURCES
    *.cpp
    )

file(GLOB_RECURSE RESOURCES
    *.cpp
    )

add_library(notificationmanager
    SHARED
    ${HEADERS}
    ${SOURCES}
    ${RESOURCES}
    )

target_link_libraries(notificationmanager
    PUBLIC
    Qt5::Core
    Qt5::Quick
    Zera::zera-timers
    )

target_include_directories(notificationmanager
    PUBLIC
    $<INSTALL_INTERFACE:include/notificationmanager>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

set_target_properties(notificationmanager PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(notificationmanager PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

generate_export_header(notificationmanager)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/notificationmanager_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/notificationmanager
    )

install(TARGETS notificationmanager
    EXPORT notificationmanagerExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

write_basic_package_version_file(
    notificationmanagerConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMinorVersion
    )

configure_file(notificationmanagerConfig.cmake.in notificationmanagerConfig.cmake @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/notificationmanagerConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/notificationmanagerConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/notificationmanager
    )

install(TARGETS notificationmanager
    EXPORT notificationmanager
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(EXPORT notificationmanagerExport
    FILE notificationmanagerTargets.cmake
    NAMESPACE ZeraQml::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/notificationmanager
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/notificationmanager
    )
