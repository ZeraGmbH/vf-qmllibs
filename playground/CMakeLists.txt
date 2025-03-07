add_executable(
    vf-qmllibs-examples
    main.cpp
    qml/app.qrc
)

target_link_libraries(
    vf-qmllibs-examples
    PRIVATE
        Qt5::Quick
        Qt5::Qml
        anmlib
        zeracomponents
        notificationmanager
        uivlib
        zerafa
        ZVKeyboardLayout
        timedate-qml-wrapper
)

install(TARGETS vf-qmllibs-examples
    EXPORT vf-qmllibs-examples
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
