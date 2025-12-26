# Inspired by
# https://github.com/KDAB/kdabtv/blob/master/Qt-Widgets-and-more/UnitTests/Tests/CMakeLists.txt
function(SETUP_QTESTS_TIMEZONE_TRANSLATIONS)
    foreach(_testname ${ARGN})
        add_test(NAME ${_testname}
                 COMMAND ${_testname})
        add_executable(${_testname}
            ${_testname}.h
            ${_testname}.cpp
            )
        target_link_libraries(${_testname}
            PUBLIC
            ${QTX}::Test
            Zera::zera-timers-testlib
            timezone-translations
        )
    endforeach()
endfunction()

SETUP_QTESTS_TIMEZONE_TRANSLATIONS(
    test_timezone_translations
)
