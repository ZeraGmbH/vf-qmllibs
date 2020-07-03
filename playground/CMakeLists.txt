project(PlayApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG")

# Tell CMake to call moc automaticly
set(CMAKE_AUTOMOC ON)


include(FeatureSummary)
include(GNUInstallDirs)

find_package(Qt5 REQUIRED COMPONENTS Quick Core Qml Widgets DBus Xml)

# Telling CMake location of our app .qrc file
qt5_add_resources(APP_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/qml/app.qrc)

# We're using ${PROJECT_NAME} for target name but it's not necessary
add_executable(
    vf-qmllibs-examples
    main.cpp        # Our example project consists only of one .cpp file

    ${APP_RESOURCES}    # App resources file
)

target_compile_features(
   vf-qmllibs-examples
    PRIVATE
        cxx_auto_type
        cxx_generic_lambdas
)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(
        vf-qmllibs-examples
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )
endif()

target_link_libraries(
    vf-qmllibs-examples
    PRIVATE

        Qt5::Core
        Qt5::Quick
        Qt5::Qml
        Qt5::DBus
        Qt5::Xml
        Qt5::Widgets
        -Wl,--whole-archive
        vfnetworkmanager
        #zeracomplib
        anmlib
        notificationmanager
        -Wl,--no-whole-archive
)

install(TARGETS vf-qmllibs-examples
    EXPORT vf-qmllibs-examples
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
