project(zeracomponents VERSION 1.0 LANGUAGES CXX C) 

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message(STATUS "Debug type: " ${CMAKE_BUILD_TYPE})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -O0 -g")
endif()
# Tell CMake to call moc automaticly
set(CMAKE_AUTOMOC ON)



set(zeracomponents_VERSION_MAJOR "0")
set(zeracomponents_VERSION_MINOR "0")
set(zeracomponents_VERSION_PATCH "1")

set(PROJECT_VERSION "${zeracomponents_VERSION_MAJOR}.${zeracomponents_VERSION_MINOR}.${zeracomponents_VERSION_PATCH}")


include(FeatureSummary)
include(GNUInstallDirs)


find_package(Qt5 CONFIG REQUIRED COMPONENTS Quick)
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
    qt5_add_resources(PLUGIN_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/zeracomponents.qrc)
else()
    qtquick_compiler_add_resources(PLUGIN_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/zeracomponents.qrc)
endif()

add_library(
    zeracomponents
    SHARED

    ${APP_HEADERS}
    ${APP_SOURCES}

    ${PLUGIN_RESOURCES}     # Plugin resources file
    )


target_compile_features(
    zeracomponents
    PRIVATE
    cxx_auto_type
    cxx_generic_lambdas
    )

target_link_libraries(
    zeracomponents
    PUBLIC
    Qt5::Quick
    PRIVATE
    qmlhelpers
    )


target_include_directories(zeracomponents
    PUBLIC
    $<INSTALL_INTERFACE:include/zeracomponents>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${header_dir_list}
    )

#set target Version
set_target_properties(zeracomponents PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zeracomponents PROPERTIES SOVERSION ${zeracomponents_VERSION_MAJOR})

#generate export header
include(GenerateExportHeader)
generate_export_header(zeracomponents)

#install export header
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zeracomponents_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zeracomponents
    )


# install library
install(TARGETS zeracomponents
    EXPORT zeracomponentsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )



# configure *ConfigVersion.cmake
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    zeracomponentsConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMinorVersion
    )


# configure *Config.cmake
configure_file(zeracomponentsConfig.cmake.in zeracomponentsConfig.cmake @ONLY)


# install *Config(Version).cmake
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/zeracomponentsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/zeracomponentsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zeracomponents
    )

# install targets cmake-files
install(EXPORT zeracomponentsExport
    FILE zeracomponentsTargets.cmake
    NAMESPACE ZeraQml::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zeracomponents
    )

# install public headers
install(
    FILES ${APP_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zeracomponents
    )


feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
