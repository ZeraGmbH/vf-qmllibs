file(GLOB_RECURSE HEADERS
    src/*.h
    )

file(GLOB_RECURSE SOURCES
    src/*.cpp
    )

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(RESOURCES zeraveincomponents.qrc)
else()
    qtquick_compiler_add_resources(RESOURCES zeraveincomponents.qrc)
endif()

add_library(zeraveincomponents
    SHARED
    ${HEADERS}
    ${SOURCES}
    ${RESOURCES}
    )

SET_QML_PATH(zeraveincomponents src/qml)

target_link_libraries(
    zeraveincomponents
    PUBLIC
    ${QTX}::Quick
    zeracomponents
    ZeraTranslation::ZeraTranslation
    )

target_include_directories(zeraveincomponents
    PUBLIC
    $<INSTALL_INTERFACE:include/zeraveincomponents>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

set_target_properties(zeraveincomponents PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zeraveincomponents PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS zeraveincomponents NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS zeraveincomponents
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zeraveincomponents
    )

