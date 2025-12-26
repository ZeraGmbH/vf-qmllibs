cmake_minimum_required(VERSION 3.0)

project(vf-qmllibs LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "1")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
project(vf-qmllibs VERSION ${PROJECT_VERSION} LANGUAGES CXX)

option(buildVein "Building libs depending on vein" ON)

set(QT_MAJOR_VER "5" CACHE STRING "Qt major version")
set(QTX "Qt${QT_MAJOR_VER}")
set(KFX "KF${QT_MAJOR_VER}")

if("${QT_MAJOR_VER}" STREQUAL "6")
    find_package(Qt6 CONFIG REQUIRED COMPONENTS Core Core5Compat Qml Quick DBus Xml Svg Test)
    find_program (QDBUSXML2CPP NAMES qdbusxml2cpp-qt6 qdbusxml2cpp REQUIRED)
else()
    find_package(Qt5 CONFIG REQUIRED COMPONENTS Core Qml Quick QuickCompiler DBus Xml Svg Test)
    find_program (QDBUSXML2CPP NAMES qdbusxml2cpp-qt5 qdbusxml2cpp REQUIRED)
endif()
find_package(FontAweSomeQml REQUIRED)
find_package(ZenuxCore REQUIRED)
find_package(ZeraTranslation REQUIRED)
find_package(SortFilterProxyModel REQUIRED)
find_package(${KFX}NetworkManagerQt REQUIRED)
find_package(${KFX}ModemManagerQt REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(QWT REQUIRED ${QTX}Qwt6)

include(FeatureSummary)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)

enable_testing()

macro(SET_QML_PATH TARGET QML_BASE)
    set(QML_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${QML_BASE})
    set(QML_IMPORT_PATH ${QML_IMPORT_PATH} ${QML_PATH} CACHE STRING "" FORCE)
    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        target_compile_definitions(${TARGET} PRIVATE QML_SRC_PATH="${QML_PATH}")
    else()
        target_compile_definitions(${TARGET} PRIVATE QML_SRC_PATH="qrc:/${QML_BASE}")
    endif()
endmacro()

write_basic_package_version_file(
    VfQmlLibsConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
    )

configure_file(VfQmlLibsConfig.cmake.in VfQmlLibsConfig.cmake @ONLY)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/VfQmlLibsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/VfQmlLibsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/VfQmlLibs
    )

install(EXPORT VfQmlLibsExport
    FILE VfQmlLibsTargets.cmake
    NAMESPACE Zera::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/VfQmlLibs
    )

if(buildVein)
    add_subdirectory(veinlibs)
endif()
add_subdirectory(libs)
add_subdirectory(playground)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
