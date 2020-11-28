cmake_minimum_required(VERSION 3.0)
project(vf-qmllibs VERSION 1.1.0 LANGUAGES CXX C)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG")
endif()


#Some of the libs are based on the ZeraVeinFramework.
#If you do not wish to use these set buildVein to OFF.
#This way this collection is useable without vein
option(buildVein "Building libs depending on vein" ON)


## These are generic qml libs useabel in and outside of vein applications
include(${PROJECT_SOURCE_DIR}/libs/libs.cmake)
## These are complete gui modules useabel in and outside of vein applications 
include(${PROJECT_SOURCE_DIR}/modules/modules.cmake)

if(buildVein)
    message(STATUS "Building with VEIN depends")
## These are qml libst with direct connection to vein
    include(${PROJECT_SOURCE_DIR}/veinlibs/veinlibs.cmake)
## These are complet gui modules with direct connection to vein
#include(${PROJECT_SOURCE_DIR}/veinmodules/veinmodules.cmake)
endif()


add_subdirectory(playground)

set(OTHER_FILES README.md)

