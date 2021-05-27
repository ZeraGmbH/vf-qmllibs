project(qmlhelpers VERSION 1.0 LANGUAGES CXX C)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message(STATUS "Debug type: " ${CMAKE_BUILD_TYPE})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -O0 -g")
endif()
# Tell CMake to call moc automaticly
set(CMAKE_AUTOMOC ON)

set(qmlhelpers_VERSION_MAJOR "0")
set(qmlhelpers_VERSION_MINOR "0")
set(qmlhelpers_VERSION_PATCH "1")
set(PROJECT_VERSION "${qmlhelpers_VERSION_MAJOR}.${qmlhelpers_VERSION_MINOR}.${qmlhelpers_VERSION_PATCH}")

include(FeatureSummary)
include(GNUInstallDirs)

find_package(Qt5 CONFIG REQUIRED COMPONENTS Quick)



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

qt5_add_resources(PLUGIN_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/qmlhelpers.qrc)

add_library(
    qmlhelpers
    SHARED

    ${APP_HEADERS}
    ${APP_SOURCES}

    ${PLUGIN_RESOURCES}     # Plugin resources file
    )

target_compile_features(
    qmlhelpers
    PRIVATE
    cxx_auto_type
    cxx_generic_lambdas
    )

target_link_libraries(
    qmlhelpers
    PUBLIC
    Qt5::Quick
    )

target_include_directories(qmlhelpers
    PUBLIC
    $<INSTALL_INTERFACE:include/qmlhelpers>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${header_dir_list}
    )

#set target Version
set_target_properties(qmlhelpers PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(qmlhelpers PROPERTIES SOVERSION ${qmlhelpers_VERSION_MAJOR})

#generate export header
include(GenerateExportHeader)
generate_export_header(qmlhelpers)

#install export header
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/qmlhelpers_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qmlhelpers
    )

# install library
install(TARGETS qmlhelpers
    EXPORT qmlhelpersExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

# configure *ConfigVersion.cmake
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    qmlhelpersConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMinorVersion
    )

# configure *Config.cmake
configure_file(qmlhelpersConfig.cmake.in qmlhelpersConfig.cmake @ONLY)

# install *Config(Version).cmake
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/qmlhelpersConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/qmlhelpersConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qmlhelpers
    )

# install targets cmake-files
install(EXPORT qmlhelpersExport
    FILE qmlhelpersTargets.cmake
    NAMESPACE ZeraQml::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qmlhelpers
    )

# install public headers
install(
    FILES ${APP_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qmlhelpers
    )

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
