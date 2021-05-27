project(uivlib VERSION 1.0 LANGUAGES CXX C) 

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message(STATUS "Debug type: " ${CMAKE_BUILD_TYPE})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -O0 -g")
endif()
# Tell CMake to call moc automaticly
set(CMAKE_AUTOMOC ON)



set(uivlib_VERSION_MAJOR "0")
set(uivlib_VERSION_MINOR "0")
set(uivlib_VERSION_PATCH "1")

set(PROJECT_VERSION "${uivlib_VERSION_MAJOR}.${uivlib_VERSION_MINOR}.${uivlib_VERSION_PATCH}")

include(FeatureSummary)
include(GNUInstallDirs)

find_package(Qt5 CONFIG REQUIRED COMPONENTS Core Gui Qml Quick)
find_package(Qt5QuickCompiler CONFIG REQUIRED)

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

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    qt5_add_resources(PLUGIN_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/uivlib.qrc)
else()
    qtquick_compiler_add_resources(PLUGIN_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/uivlib.qrc)
endif()

add_library(
    uivlib
    SHARED

    ${APP_HEADERS}
    ${APP_SOURCES}

    ${PLUGIN_RESOURCES}     # Plugin resources file
    )

target_compile_features(
    uivlib
    PRIVATE
    cxx_auto_type
    cxx_generic_lambdas
    )

target_link_libraries(
    uivlib
    PUBLIC
    Qt5::Core
    Qt5::Quick
    Qt5::Qml
    )

target_include_directories(uivlib
    PUBLIC
    $<INSTALL_INTERFACE:include/uivlib>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${header_dir_list}
    )

#set target Version
set_target_properties(uivlib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(uivlib PROPERTIES SOVERSION ${uivlib_VERSION_MAJOR})

#generate export header
include(GenerateExportHeader)
generate_export_header(uivlib)

#install export header
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/uivlib_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/uivlib
    )

# install library
install(TARGETS uivlib
    EXPORT uivlibExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

# configure *ConfigVersion.cmake
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    uivlibConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMinorVersion
    )

# configure *Config.cmake
configure_file(uivlibConfig.cmake.in uivlibConfig.cmake @ONLY)

# install *Config(Version).cmake
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/uivlibConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/uivlibConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/uivlib
    )

# install targets cmake-files
install(EXPORT uivlibExport
    FILE uivlibTargets.cmake
    NAMESPACE ZeraQml::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/uivlib
    )

# install public headers
install(
    FILES ${APP_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/uivlib
    )


feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
