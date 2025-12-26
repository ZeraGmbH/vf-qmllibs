file(GLOB_RECURSE HEADERS
    *.h
    )

file(GLOB_RECURSE SOURCES
    *.cpp
    )

add_library(notificationmanager-static
    STATIC
    ${HEADERS}
    ${SOURCES}
    )

target_link_libraries(notificationmanager-static
    PUBLIC
    ${QTX}::Core
    Zera::zera-timers
    )

target_include_directories(notificationmanager-static
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )
