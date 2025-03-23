#include "test_tasks_datetime.h"
#include "tasksetdatetime.h"
#include "tasksetntp.h"
#include "tasksettimezone.h"
#include <timemachineobject.h>
#include <signalspywaiter.h>
#include <QDate>
#include <QTime>
#include <QSignalSpy>
#include <QTest>

QTEST_MAIN(test_tasks_datetime)

static constexpr int waitTimeForStartOrSync = 10;
static constexpr int test_year = 2025;
static constexpr int test_month = 3;
static constexpr int test_day = 24;
static constexpr int test_hour = 14;
static constexpr int test_minute = 42;
static constexpr int test_second = 31;

void test_tasks_datetime::init()
{
    TestTimedate1Connection::setCanNtp(true);
    QDate date(test_year, test_month, test_day);
    QTime time(test_hour, test_minute, test_second);
    m_testDatetime = QDateTime(date, time);

    m_timeDateConnection = std::make_shared<TestTimedate1Connection>(waitTimeForStartOrSync);
    QSignalSpy spyTimezonesAvail(m_timeDateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged);
    m_timeDateConnection->start();
    SignalSpyWaiter::waitForSignals(&spyTimezonesAvail, 1, waitTimeForStartOrSync);
}


void test_tasks_datetime::setDateTimeNotSucessful()
{
    TaskSetDateTime task(m_timeDateConnection,
                         m_testDatetime);
    QSignalSpy spy(&task, &TaskTemplate::sigFinish);
    task.start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], false);
    QVERIFY(m_testDatetime != m_timeDateConnection->getDateTimeSetSuccessfully());
}

void test_tasks_datetime::setDateTimeSucessful()
{
    // To set time we need NTP off
    m_timeDateConnection->setNtpActive(false);
    TimeMachineObject::feedEventLoop();

    TaskSetDateTime task(m_timeDateConnection,
                         m_testDatetime);
    QSignalSpy spy(&task, &TaskTemplate::sigFinish);
    task.start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], true);
    QCOMPARE(m_testDatetime, m_timeDateConnection->getDateTimeSetSuccessfully());
}

void test_tasks_datetime::setNtpOffOn()
{
    TaskSetNtp taskOff(m_timeDateConnection,
                       false);
    QSignalSpy spyOff(&taskOff, &TaskTemplate::sigFinish);
    taskOff.start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spyOff.count(), 1);
    QCOMPARE(spyOff[0][0], true);
    QCOMPARE(m_timeDateConnection->getNtpActive(), false);

    TaskSetNtp taskOn(m_timeDateConnection,
                      true);
    QSignalSpy spyOn(&taskOff, &TaskTemplate::sigFinish);
    taskOn.start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spyOn.count(), 1);
    QCOMPARE(spyOn[0][0], true);
    QCOMPARE(m_timeDateConnection->getNtpActive(), true);
}

void test_tasks_datetime::setNtpNotAvail()
{
    TestTimedate1Connection::setCanNtp(false);
    TaskSetNtp taskOff(m_timeDateConnection,
                       false);
    QSignalSpy spyOff(&taskOff, &TaskTemplate::sigFinish);
    taskOff.start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spyOff.count(), 1);
    QCOMPARE(spyOff[0][0], false);
    QCOMPARE(m_timeDateConnection->getNtpActive(), true);
}

void test_tasks_datetime::setTimezoneNotSuccesful()
{
    TaskSetTimezone task(m_timeDateConnection,
                         "foo");
    QSignalSpy spy(&task, &TaskTemplate::sigFinish);
    task.start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], false);
    QCOMPARE(m_timeDateConnection->getTimeszone(), TestTimedate1Connection::getDefaultTimezone());
}

void test_tasks_datetime::setTimezoneSuccesful()
{
    TaskSetTimezone task(m_timeDateConnection,
                         "Europe/Zurich");
    QSignalSpy spy(&task, &TaskTemplate::sigFinish);
    task.start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], true);
    QCOMPARE(m_timeDateConnection->getTimeszone(), "Europe/Zurich");
}
