#include "test_tasks_datetime.h"
#include "tasksetdatetime.h"
#include "tasksetntp.h"
#include "tasksettimezone.h"
#include "tasksetalldatetime.h"
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


void test_tasks_datetime::setDateTimeFail()
{
    int errorIndicator = 0;
    TaskTemplatePtr task = TaskSetDateTime::create(m_timeDateConnection,
                                                   m_testDatetime,
                                                   [&]() { errorIndicator = 42; });
    QSignalSpy spy(task.get(), &TaskTemplate::sigFinish);
    task->start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], false);
    QCOMPARE(errorIndicator, 42);
    QVERIFY(m_testDatetime != m_timeDateConnection->getDateTimeSetSuccessfully());
}

void test_tasks_datetime::setDateTimePass()
{
    // To set time we need NTP off
    m_timeDateConnection->setNtpActive(false);
    TimeMachineObject::feedEventLoop();

    int errorIndicator = 0;
    TaskTemplatePtr task = TaskSetDateTime::create(m_timeDateConnection,
                                                   m_testDatetime,
                                                   [&]() { errorIndicator = 42; });
    QSignalSpy spy(task.get(), &TaskTemplate::sigFinish);
    task->start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], true);
    QCOMPARE(errorIndicator, 0);
    QCOMPARE(m_testDatetime, m_timeDateConnection->getDateTimeSetSuccessfully());
}

void test_tasks_datetime::setNtpOffOnPass()
{
    int errorIndicatorOff = 0;
    TaskTemplatePtr taskOff = TaskSetNtp::create(m_timeDateConnection,
                                              false,
                                              [&]() { errorIndicatorOff = 42; });
    QSignalSpy spyOff(taskOff.get(), &TaskTemplate::sigFinish);
    taskOff->start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spyOff.count(), 1);
    QCOMPARE(spyOff[0][0], true);
    QCOMPARE(m_timeDateConnection->getNtpActive(), false);
    QCOMPARE(errorIndicatorOff, 0);

    int errorIndicatorOn = 0;
    TaskTemplatePtr taskOn = TaskSetNtp::create(m_timeDateConnection,
                                                 true,
                                                 [&]() { errorIndicatorOn = 42; });
    QSignalSpy spyOn(taskOn.get(), &TaskTemplate::sigFinish);
    taskOn->start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spyOn.count(), 1);
    QCOMPARE(spyOn[0][0], true);
    QCOMPARE(m_timeDateConnection->getNtpActive(), true);
    QCOMPARE(errorIndicatorOn, 0);
}

void test_tasks_datetime::setNtpFail()
{
    TestTimedate1Connection::setCanNtp(false);
    int errorIndicatorOff = 0;
    TaskTemplatePtr taskOff = TaskSetNtp::create(m_timeDateConnection,
                                                 false,
                                                 [&]() { errorIndicatorOff = 42; });
    QSignalSpy spyOff(taskOff.get(), &TaskTemplate::sigFinish);
    taskOff->start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spyOff.count(), 1);
    QCOMPARE(spyOff[0][0], false);
    QCOMPARE(m_timeDateConnection->getNtpActive(), true);
    QCOMPARE(errorIndicatorOff, 42);
}

void test_tasks_datetime::setTimezoneFail()
{
    int errorIndicator = 0;
    TaskTemplatePtr task = TaskSetTimezone::create(m_timeDateConnection,
                                                   "foo",
                                                   [&]() { errorIndicator = 42; });
    QSignalSpy spy(task.get(), &TaskTemplate::sigFinish);
    task->start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], false);
    QCOMPARE(m_timeDateConnection->getTimeszone(), TestTimedate1Connection::getDefaultTimezone());
    QCOMPARE(errorIndicator, 42);
}

void test_tasks_datetime::setTimezonePass()
{
    int errorIndicator = 0;
    TaskTemplatePtr task = TaskSetTimezone::create(m_timeDateConnection,
                                                   "Europe/Zurich",
                                                   [&]() { errorIndicator = 42; });

    QSignalSpy spy(task.get(), &TaskTemplate::sigFinish);
    task->start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], true);
    QCOMPARE(m_timeDateConnection->getTimeszone(), "Europe/Zurich");
    QCOMPARE(errorIndicator, 0);
}

void test_tasks_datetime::setAllSetTimezoneFail()
{
    std::shared_ptr<QStringList> errors = std::make_shared<QStringList>();
    TaskTemplatePtr task = TaskSetAllDateTime::create(m_timeDateConnection,
                                                   "foo", false, m_testDatetime,
                                                   errors);
    QSignalSpy spy(task.get(), &TaskTemplate::sigFinish);
    task->start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], false);
    QCOMPARE(errors->count(), 1);
    QCOMPARE(errors->at(0), "Set timezone failed!");
}

void test_tasks_datetime::setAllSetNtpFail()
{
    TestTimedate1Connection::setCanNtp(false);
    std::shared_ptr<QStringList> errors = std::make_shared<QStringList>();
    TaskTemplatePtr task = TaskSetAllDateTime::create(m_timeDateConnection,
                                                   "Europe/Zurich", false, m_testDatetime,
                                                   errors);
    QSignalSpy spy(task.get(), &TaskTemplate::sigFinish);
    task->start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], false);
    QCOMPARE(errors->count(), 1);
    QCOMPARE(errors->at(0), "NTP deactivate failed!");
}

void test_tasks_datetime::setAllSetDateTimeFail()
{
    std::shared_ptr<QStringList> errors = std::make_shared<QStringList>();
    TaskTemplatePtr task = TaskSetAllDateTime::create(m_timeDateConnection,
                                                   "Europe/Zurich", false, QDateTime(),
                                                   errors);
    QSignalSpy spy(task.get(), &TaskTemplate::sigFinish);
    task->start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], false);
    QCOMPARE(errors->count(), 1);
    QCOMPARE(errors->at(0), "Set date/time failed!");
}

void test_tasks_datetime::setAllPass()
{
    std::shared_ptr<QStringList> errors = std::make_shared<QStringList>();
    TaskTemplatePtr task = TaskSetAllDateTime::create(m_timeDateConnection,
                                                   "Europe/Zurich", false, m_testDatetime,
                                                   errors);
    QSignalSpy spy(task.get(), &TaskTemplate::sigFinish);
    task->start();
    TimeMachineObject::feedEventLoop();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0], true);
    QCOMPARE(errors->count(), 0);
}
