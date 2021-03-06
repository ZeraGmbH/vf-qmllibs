project(PlayApp VERSION 1.0 LANGUAGES CXX)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG")
endif()

# Tell CMake to call moc automaticly
set(CMAKE_AUTOMOC ON)

include(FeatureSummary)
include(GNUInstallDirs)

find_package(Qt5 REQUIRED COMPONENTS Quick Core Qml Widgets DBus Xml)
find_package(Qt5QuickCompiler CONFIG REQUIRED)
find_package(ZeraTranslation REQUIRED)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    qt5_add_resources(APP_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/qml/app.qrc)
else()
    qtquick_compiler_add_resources(APP_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/qml/app.qrc)
endif()

# We're using ${PROJECT_NAME} for target name but it's not necessary
add_executable(
    vf-qmllibs-examples
    main.cpp        # Our example project consists only of one .cpp file

    ${APP_RESOURCES}    # App resources file
)

target_link_libraries(
    vf-qmllibs-examples
    PRIVATE
        Qt5::Core
        Qt5::Quick
        Qt5::Qml
        Qt5::DBus
        Qt5::Xml
        Qt5::Widgets
        ZeraTranslation::ZeraTranslation
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

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
