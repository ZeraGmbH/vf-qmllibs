file(GLOB_RECURSE HEADERS
    src/*.h
    )

file(GLOB_RECURSE SOURCES
    src/*.cpp
    )

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_subdirectory("src/qml")
else()
    qtquick_compiler_add_resources(RESOURCES zeracomponents.qrc)
endif()

add_library(zeracomponents
    SHARED
    ${HEADERS}
    ${SOURCES}
    ${RESOURCES}
    )

SET_QML_PATH(zeracomponents src/qml)

target_link_libraries(
    zeracomponents
    PUBLIC
    qmlhelpers
    timedate-qml-wrapper
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

