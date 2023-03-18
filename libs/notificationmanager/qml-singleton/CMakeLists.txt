add_library(notificationmanager
    SHARED
    globalusernotificationsingleton.h
    globalusernotificationsingleton.cpp
    notificationmanager.qrc
    )

target_link_libraries(notificationmanager
    PUBLIC
    Qt5::Quick
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
