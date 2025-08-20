add_definitions(-DTEST_SVG_FILE_PATH="${CMAKE_CURRENT_BINARY_DIR}/TestSvgs/")

# Inspired by
# https://github.com/KDAB/kdabtv/blob/master/Qt-Widgets-and-more/UnitTests/Tests/CMakeLists.txt
function(SETUP_QTESTS_VECTOR_DIAGRAM)
    foreach(_testname ${ARGN})
        add_test(NAME ${_testname}
                 COMMAND ${_testname})
        add_executable(${_testname}
            ${_testname}.h
            ${_testname}.cpp
            test-data/test-svgs.qrc
            )
        target_link_libraries(${_testname}
            PUBLIC
            Qt5::Test
            Zera::zera-timers-testlib
            Zera::testlib-common
            Zera::xml-compare-testlib
            vector-diagram-lib
            vector-diagram-testlib
        )
    endforeach()
endfunction()

SETUP_QTESTS_VECTOR_DIAGRAM(
    test_primitive_painter
    test_coord_cross_and_circle
    test_vector_default_settings
    test_vector_standard
    test_vector_type
    test_vector_style
    test_vector_nominal_maximum
    test_vector_arrow_head
    test_vectors_long_short_limits
    test_vector_line_width
    test_vector_label_font_size
    test_vector_label_collision
    test_vector_calc
)
