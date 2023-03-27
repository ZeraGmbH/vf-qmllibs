file(GLOB HEADERS
    include/*.h
)

file(GLOB_RECURSE SOURCES
    *.cpp
)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    qt5_add_resources(RESOURCES ${CMAKE_CURRENT_LIST_DIR}/zvkeyboard.qrc)
else()
    qtquick_compiler_add_resources(RESOURCES ${CMAKE_CURRENT_LIST_DIR}/zvkeyboard.qrc)
endif()

add_library(ZVKeyboard
    SHARED
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

SET_QML_PATH(ZVKeyboard qml)

target_link_libraries(ZVKeyboard
    PUBLIC
    Qt5::Core
    Qt5::Qml
)

target_include_directories(ZVKeyboard
    PUBLIC
        $<INSTALL_INTERFACE:include/zvkeyboard>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

set_target_properties(ZVKeyboard PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(ZVKeyboard PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS ZVKeyboard NAMESPACE Zera:: FILE VfQmlLibsTargets.cmake)
install(TARGETS ZVKeyboard
    EXPORT VfQmlLibsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zvkeyboard
)

