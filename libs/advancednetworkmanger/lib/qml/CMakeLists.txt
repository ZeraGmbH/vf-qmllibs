file(GLOB_RECURSE QML_FILES *qml*)

add_custom_target(network-settings-qml ALL
    SOURCES ${QML_FILES}
    )
