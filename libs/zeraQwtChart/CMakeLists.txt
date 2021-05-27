project(qwtcharts VERSION 1.0 LANGUAGES CXX C) 

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message(STATUS "Debug type: " ${CMAKE_BUILD_TYPE})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -O0 -g")
endif()
# Tell CMake to call moc automaticly
set(CMAKE_AUTOMOC ON)

set(qwtcharts_VERSION_MAJOR "0")
set(qwtcharts_VERSION_MINOR "0")
set(qwtcharts_VERSION_PATCH "1")

set(PROJECT_VERSION "${qwtcharts_VERSION_MAJOR}.${qwtcharts_VERSION_MINOR}.${qwtcharts_VERSION_PATCH}")

include(FeatureSummary)
include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)
pkg_check_modules(QWT REQUIRED Qt5Qwt6)
find_package(Qt5 CONFIG REQUIRED COMPONENTS Core Qml Quick)



MACRO(HEADER_DIRECTORIES dir return_list)
FILE(GLOB_RECURSE new_list ${dir}/*.h)
SET(dir_list "")
FOREACH(file_path ${new_list})
GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
SET(dir_list ${dir_list} ${dir_path})
ENDFOREACH()
LIST(REMOVE_DUPLICATES dir_list)
SET(${return_list} ${dir_list})
ENDMACRO()

file(GLOB_RECURSE APP_HEADERS
    src/*.h
    )

file(GLOB_RECURSE APP_SOURCES
    src/*.cpp
    )

HEADER_DIRECTORIES("src" header_dir_list)
include_directories(${header_dir_list})

qt5_add_resources(PLUGIN_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/qwtcharts.qrc)

add_library(
    qwtcharts
    SHARED

    ${APP_HEADERS}
    ${APP_SOURCES}

    ${PLUGIN_RESOURCES}     # Plugin resources file
    )


target_compile_features(
    qwtcharts
    PRIVATE
    cxx_auto_type
    cxx_generic_lambdas
    )

target_link_libraries(
    qwtcharts
    PUBLIC
    Qt5::Core
    Qt5::Quick
    Qt5::Qml
    ${QWT_LIBRARIES}
    )

target_include_directories(qwtcharts
    PUBLIC
    $<INSTALL_INTERFACE:include/qwtcharts>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE
    ${QWT_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${header_dir_list}
    )

#set target Version
set_target_properties(qwtcharts PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(qwtcharts PROPERTIES SOVERSION ${qwtcharts_VERSION_MAJOR})

#generate export header
include(GenerateExportHeader)
generate_export_header(qwtcharts)

#install export header
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/qwtcharts_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qwtcharts
    )

# install library
install(TARGETS qwtcharts
    EXPORT qwtchartsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

# configure *ConfigVersion.cmake
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    qwtchartsConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMinorVersion
    )

# configure *Config.cmake
configure_file(qwtchartsConfig.cmake.in qwtchartsConfig.cmake @ONLY)

# install *Config(Version).cmake
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/qwtchartsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/qwtchartsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qwtcharts
    )

# install targets cmake-files
install(EXPORT qwtchartsExport
    FILE qwtchartsTargets.cmake
    NAMESPACE ZeraQml::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qwtcharts
    )

# install public headers
install(
    FILES ${APP_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qwtcharts
    )

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
