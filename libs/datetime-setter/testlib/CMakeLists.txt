file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

file(GLOB HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )

add_library(timedate1-interface-testlib STATIC
    ${SOURCES}
    ${HEADER}
    resources/datetime_setter_test.qrc
)

target_include_directories(timedate1-interface-testlib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/timedate1-interface-testlib>
    )

target_link_libraries(timedate1-interface-testlib
    PUBLIC
    timedate1-interface
)
