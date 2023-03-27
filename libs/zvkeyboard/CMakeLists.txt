file(GLOB HEADERS
    *.h
)

file(GLOB_RECURSE SOURCES
    *.cpp
)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(RESOURCES zvkeyboard.qrc)
else()
    qtquick_compiler_add_resources(RESOURCES zvkeyboard.qrc)
endif()

add_library(ZVKeyboardLayout
    SHARED
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

SET_QML_PATH(ZVKeyboardLayout zvkeyboard/layouts)

target_link_libraries(ZVKeyboardLayout
    PUBLIC
    Qt5::Core
    Qt5::Qml
)

target_include_directories(ZVKeyboardLayout
    PUBLIC
        $<INSTALL_INTERFACE:include/zvkeyboard>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_target_properties(ZVKeyboardLayout PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(ZVKeyboardLayout PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS ZVKeyboardLayout NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS ZVKeyboardLayout
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zvkeyboard
)

