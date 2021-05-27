project(zeraveincomponents VERSION 1.0 LANGUAGES CXX C) 

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message(STATUS "Debug type: " ${CMAKE_BUILD_TYPE})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -O0 -g")
endif()
# Tell CMake to call moc automaticly
set(CMAKE_AUTOMOC ON)

set(zeraveincomponents_VERSION_MAJOR "0")
set(zeraveincomponents_VERSION_MINOR "0")
set(zeraveincomponents_VERSION_PATCH "1")
set(PROJECT_VERSION "${zeraveincomponents_VERSION_MAJOR}.${zeraveincomponents_VERSION_MINOR}.${zeraveincomponents_VERSION_PATCH}")

include(FeatureSummary)
include(GNUInstallDirs)

find_package(Qt5 CONFIG REQUIRED COMPONENTS Quick)
find_package(Qt5QuickCompiler CONFIG REQUIRED)
find_package(ZeraTranslation REQUIRED)

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
    qt5_add_resources(PLUGIN_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/zeraveincomponents.qrc)
else()
    qtquick_compiler_add_resources(PLUGIN_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/zeraveincomponents.qrc)
endif()

add_library(
    zeraveincomponents
    SHARED

    ${APP_HEADERS}
    ${APP_SOURCES}

    ${PLUGIN_RESOURCES}     # Plugin resources file
    )

target_compile_features(
    zeraveincomponents
    PRIVATE
    )

target_link_libraries(
    zeraveincomponents
    PUBLIC
    Qt5::Quick
    PRIVATE
    zeracomponents
    ZeraTranslation::ZeraTranslation
    )

target_include_directories(zeraveincomponents
    PUBLIC
    $<INSTALL_INTERFACE:include/zeraveincomponents>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${header_dir_list}
    )

#set target Version
set_target_properties(zeraveincomponents PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zeraveincomponents PROPERTIES SOVERSION ${zeraveincomponents_VERSION_MAJOR})

#generate export header
include(GenerateExportHeader)
generate_export_header(zeraveincomponents)

#install export header
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zeraveincomponents_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zeraveincomponents
    )

# install library
install(TARGETS zeraveincomponents
    EXPORT zeraveincomponentsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

# configure *ConfigVersion.cmake
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    zeraveincomponentsConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMinorVersion
    )

# configure *Config.cmake
configure_file(zeraveincomponentsConfig.cmake.in zeraveincomponentsConfig.cmake @ONLY)

# install *Config(Version).cmake
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/zeraveincomponentsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/zeraveincomponentsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zeraveincomponents
    )

# install targets cmake-files
install(EXPORT zeraveincomponentsExport
    FILE zeraveincomponentsTargets.cmake
    NAMESPACE ZeraQml::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zeraveincomponents
    )

# install public headers
install(
    FILES ${APP_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zeraveincomponents
    )

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
