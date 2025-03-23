#include "test_time_date_helper.h"
#include "timedatehelper.h"
#include "testtimedate1connection.h"
#include <timemachineobject.h>
#include "signalspywaiter.h"
#include <QSignalSpy>
#include <QTest>

QTEST_MAIN(test_time_date_helper)

static constexpr int waitTimeForStartOrSync = 10;

void test_time_date_helper::init()
{
    m_timeDateConnection = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
}

void test_time_date_helper::daysInMonth()
{
    TimeDateHelper facade(m_timeDateConnection);
    QCOMPARE(facade.maxDaysInYearMonth(2025, 2), 28);
    QCOMPARE(facade.maxDaysInYearMonth(2028, 2), 29);
}

void test_time_date_helper::ntpChange()
{
    TimeDateHelper facade(m_timeDateConnection);
    QSignalSpy spyNtpChange(&facade, &TimeDateHelper::sigNtpActiveChanged);

    m_timeDateConnection->setNtpActive(false);
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spyNtpChange.count(), 1);
    QCOMPARE(facade.getNtpActive(), false);

    m_timeDateConnection->setNtpActive(true);
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spyNtpChange.count(), 2);
    QCOMPARE(facade.getNtpActive(), true);
}
