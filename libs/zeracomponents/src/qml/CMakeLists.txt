file(GLOB_RECURSE QML_FILES *qml*)

add_custom_target(zera-components-qml ALL
    SOURCES ${QML_FILES}
    )
