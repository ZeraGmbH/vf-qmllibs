cmake_minimum_required(VERSION 3.0)

project(vf-qmllibs LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "1")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
project(vf-qmllibs VERSION ${PROJECT_VERSION} LANGUAGES CXX)

find_package(Qt5 CONFIG REQUIRED COMPONENTS Core Qml Quick QuickCompiler Test)
find_package(ZenuxCore REQUIRED)
find_package(ZeraTranslation REQUIRED)
find_package(SortFilterProxyModelCmake REQUIRED)
find_package(KF5NetworkManagerQt REQUIRED)
find_package(KF5ModemManagerQt REQUIRED)

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
            notificationmanager
            Zera::zera-timers-testlib
        )
    endforeach()
endfunction()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG")
endif()

# Some of the libs are based on the ZeraVeinFramework.
# If you do not wish to use these set buildVein to OFF.
# This way this collection is useable without vein
option(buildVein "Building libs depending on vein" ON)

if(buildVein)
    add_subdirectory(veinlibs)
endif()
add_subdirectory(libs)
add_subdirectory(modules)
add_subdirectory(playground)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
