#include "test_timedate1_mock.h"
#include "timedate1connection.h"
#include <QSignalSpy>
#include <QTest>

QTEST_MAIN(test_timedate1_mock)

void test_timedate1_mock::availableTimezones()
{
    Timedate1Connection connection;
    connection.connectDbus();

    //QTest::qWait(3000);
}

