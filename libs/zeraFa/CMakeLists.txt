file(GLOB_RECURSE HEADERS
    *.h
    )

file(GLOB_RECURSE SOURCES
    *.cpp
    )

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(RESOURCES zerafa.qrc)
else()
    qtquick_compiler_add_resources(RESOURCES zerafa.qrc)
endif()

add_library(zerafa
    SHARED
    ${HEADERS}
    ${SOURCES}
    ${RESOURCES}
    )

SET_QML_PATH(zerafa qml)

target_link_libraries(zerafa
    PUBLIC
    ${QTX}::Quick
    ${QTX}::Qml
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

