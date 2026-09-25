file(GLOB_RECURSE HEADERS
    lib/*.h
    )

file(GLOB_RECURSE SOURCES
    lib/*.cpp
    )

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_subdirectory("lib/qml")
else()
    qtquick_compiler_add_resources(RESOURCES zeracomponents.qrc)
endif()

add_library(zeracomponents
    SHARED
    ${HEADERS}
    ${SOURCES}
    ${RESOURCES}
    )

SET_QML_PATH(zeracomponents lib/qml)

target_link_libraries(
    zeracomponents
    PUBLIC
    qmlhelpers
    timedate-qml-wrapper
    pixmap-item
    zerafa
    )

target_include_directories(zeracomponents
    PUBLIC
    $<INSTALL_INTERFACE:include/zeracomponents>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
    )

if("${QT_MAJOR_VER}" STREQUAL "6")
    target_link_libraries(zeracomponents
        PRIVATE
            Qt6::Core5Compat
    )
endif()

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

