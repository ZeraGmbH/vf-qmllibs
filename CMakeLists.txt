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

find_package(Qt5 CONFIG REQUIRED COMPONENTS Core Qml Quick QuickCompiler DBus Xml Test)
find_package(ZenuxCore REQUIRED)
find_package(ZeraTranslation REQUIRED)
find_package(SortFilterProxyModel REQUIRED)
find_package(KF5NetworkManagerQt REQUIRED)
find_package(KF5ModemManagerQt REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(QWT REQUIRED Qt5Qwt6)

include(FeatureSummary)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)

enable_testing()
# Inspired by
# https://github.com/KDAB/kdabtv/blob/master/Qt-Widgets-and-more/UnitTests/Tests/CMakeLists.txt
function(SETUP_QTESTS)
    foreach(_testname ${ARGN})
        add_test(NAME ${_testname}
                 COMMAND ${_testname})
        add_executable(${_testname}
            ${_testname}.h
            ${_testname}.cpp
            )
        target_link_libraries(${_testname}
            PUBLIC
            Qt5::Test
            notificationmanager-static
            Zera::zera-timers-testlib
        )
    endforeach()
endfunction()

macro(SET_QML_PATH TARGET QML_BASE)
    set(QML_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${QML_BASE})
    set(QML_IMPORT_PATH ${QML_IMPORT_PATH} ${QML_PATH} CACHE STRING "" FORCE)
    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        target_compile_definitions(${TARGET} PRIVATE QML_SRC_PATH="${QML_PATH}")
    else()
        target_compile_definitions(${TARGET} PRIVATE QML_SRC_PATH="qrc:/${QML_BASE}")
    endif()
endmacro()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG")
endif()

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
