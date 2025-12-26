file(GLOB_RECURSE HEADERS
    *.h
    )

file(GLOB_RECURSE SOURCES
    *.cpp
    )

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(RESOURCES notificationmanager.qrc)
else()
    qtquick_compiler_add_resources(RESOURCES notificationmanager.qrc)
endif()

add_library(notificationmanager
    SHARED
    ${HEADERS}
    ${SOURCES}
    ${RESOURCES}
    )

SET_QML_PATH(notificationmanager qml)

target_link_libraries(notificationmanager
    PUBLIC
    ${QTX}::Quick
    PRIVATE
    notificationmanager-static
    )

target_include_directories(notificationmanager
    PUBLIC
    $<INSTALL_INTERFACE:include/notificationmanager>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

set_target_properties(notificationmanager PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(notificationmanager PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS notificationmanager NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS notificationmanager
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/notificationmanager
    )
