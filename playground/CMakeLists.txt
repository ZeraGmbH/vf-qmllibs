add_executable(
    vf-qmllibs-examples
    main.cpp
    qml/app.qrc
)

target_link_libraries(
    vf-qmllibs-examples
    PRIVATE
        Qt5::Core
        Qt5::Quick
        Qt5::Qml
        anmlib
        zeracomponents
        notificationmanager
        uivlib
        zerafa
)

install(TARGETS vf-qmllibs-examples
    EXPORT vf-qmllibs-examples
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
