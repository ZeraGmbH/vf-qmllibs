# Inspired by
# https://github.com/KDAB/kdabtv/blob/master/Qt-Widgets-and-more/UnitTests/Tests/CMakeLists.txt
function(SETUP_QTESTS_TIMEDATE1)
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
            timedate1-interface
            timedate1-interface-testlib
            Zera::zera-timers-testlib
            Zera::testlib-common
        )
    endforeach()
endfunction()

SETUP_QTESTS_TIMEDATE1(
    test_timezone_extractor
    test_timedate1_connection
    test_timezone_model_city_filtered
    test_timezone_model_region
    test_timezone_state_controller
    test_time_date_helper
)
