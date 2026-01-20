add_executable(
    vf-qmllibs-examples
    main.cpp
    qml/app.qrc
)

target_link_libraries(
    vf-qmllibs-examples
    PRIVATE
        ${QTX}::Quick
        ${QTX}::Qml
        anmlib
        zeracomponents
        notificationmanager
        zerafa
        ZVKeyboardLayout
        timedate-qml-wrapper
        line-charts-qt
)

install(TARGETS vf-qmllibs-examples
    EXPORT vf-qmllibs-examples
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
