add_definitions(-DTEST_SVG_FILE_PATH="${CMAKE_CURRENT_BINARY_DIR}/TestSvgs/")

# Inspired by
# https://github.com/KDAB/kdabtv/blob/master/Qt-Widgets-and-more/UnitTests/Tests/CMakeLists.txt
function(SETUP_QTESTS_VECTORDIAGRAM)
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
            Zera::zera-timers-testlib
            Zera::testlib-common
            Zera::xml-compare-testlib
            uivlib
        )
    endforeach()
endfunction()

SETUP_QTESTS_VECTORDIAGRAM(
    test_vector_diagram_gui
)

target_sources(test_vector_diagram_gui
    PRIVATE
    test-data/test-svgs.qrc
)
