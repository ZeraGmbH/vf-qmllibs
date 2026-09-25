enable_testing()

file(GLOB TESTFILES
    ${CMAKE_CURRENT_SOURCE_DIR}/testfiles/*
)

add_custom_target(journalansilineconvert-testfiles ALL
    SOURCES ${TESTFILES}
    )

# Inspired by
# https://github.com/KDAB/kdabtv/blob/master/Qt-Widgets-and-more/UnitTests/Tests/CMakeLists.txt
function(SETUP_TESTS)
    foreach(_testname ${ARGN})
        add_test(NAME ${_testname}
                 COMMAND ${_testname}
        )
        add_executable(${_testname}
            ${_testname}.h
            ${_testname}.cpp
        )
        target_include_directories(${_testname}
            PRIVATE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
            ${CMAKE_CURRENT_SOURCE_DIR}
        )
        target_compile_definitions(${_testname}
            PRIVATE
            TESTFILE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/testfiles/"
        )
        target_link_libraries(${_testname}
            PUBLIC
            ${QTX}::Test
            zeracomponents
            Zera::testlib-common
            Zera::zera-timers-testlib
        )
    endforeach()
endfunction()

SETUP_TESTS(
    test_journalansilineconvert
)
