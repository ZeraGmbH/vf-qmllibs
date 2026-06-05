function(SETUP_QTESTS_NETWORK_MANAGER)
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
            anmlib
            Zera::zera-timers-testlib
            Zera::testlib-common
        )
    endforeach()
endfunction()

SETUP_QTESTS_NETWORK_MANAGER (
    test_deduce_subnetmask_ipv4
)
