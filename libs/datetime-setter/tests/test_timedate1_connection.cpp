#include "test_timedate1_connection.h"
#include "timedate1connection.h"
#include "testtimedate1connection.h"
#include <qtestcase.h>
#include <signalspywaiter.h>
#include <QTest>

QTEST_MAIN(test_timedate1_connection)

void test_timedate1_connection::initTestCase_data()
{
    QTest::addColumn<QString>("testType");
    QTest::newRow("Test") << QString("Test");

    // QSKIP alike:
    // Uncomment 'QTest::newRow("Production")...' below for manual tests of Timedate1Connection
    // Be aware that manual (production) tests
    // * touch NTP/timezone settings and polkit asks for password! So in case of error
    //   it is strongly recommended to ask 'timedatectl status' to check if dev-host is
    //   still in state expected
    // * take very long due to waiting on NtpSync here and there
    //QTest::newRow("Production") << QString("Production");
}

void test_timedate1_connection::init()
{
    setupConnection(m_connection);

    QSignalSpy spyStart(m_connection.get(), &Timedate1Connection::sigAvailTimezonesChanged);
    m_connection->start();
    SignalSpyWaiter::waitForSignals(&spyStart, 1, m_waitTimeNoPolkit);
    QCOMPARE(spyStart.count(), 1);

    m_hostTimezone = m_connection->getTimeszone();

    // Make sure NTP is on and synced
    Q_ASSERT(m_connection->getNtpActive());
    Q_ASSERT(m_connection->getNtpSynced());
}

void test_timedate1_connection::cleanup()
{
    // Make sure tests leave with timezone entered and NTP on + synced
    qInfo("Cleanup: Activate NTP");
    QSignalSpy spyNtpSet(m_connection.get(), &Timedate1Connection::sigNtpActiveSet);
    m_connection->setNtpActive(true);
    SignalSpyWaiter::waitForSignals(&spyNtpSet, 1, m_waitTimeNoPolkit);

    qInfo("Cleanup: Restore timezone %s", qPrintable(m_hostTimezone));
    QSignalSpy spyTimezoneSet(m_connection.get(), &Timedate1Connection::sigTimezoneSet);
    m_connection->setTimezone(m_hostTimezone);
    SignalSpyWaiter::waitForSignals(&spyTimezoneSet, 1, m_waitTimeNoPolkit);

    if (!m_connection->getNtpSynced())
        waitNtpSync();

    Q_ASSERT(m_connection->getNtpActive());
    Q_ASSERT(m_connection->getNtpSynced());

    m_connection.reset();
}

void test_timedate1_connection::availableTimezones()
{
    QStringList availTimezones = m_connection->getAvailTimezones();
    QVERIFY(!availTimezones.isEmpty());
    qInfo("All timezones:");
    qInfo("%s", qPrintable(availTimezones.join("\n")));
}

void test_timedate1_connection::disableNtp()
{
    QSignalSpy spyNtpAvailable(m_connection.get(), &Timedate1Connection::sigNtpAvailableChanged);
    QSignalSpy spyNtpActive(m_connection.get(), &Timedate1Connection::sigNtpActiveChanged);
    QSignalSpy spyNtpSynced(m_connection.get(), &Timedate1Connection::sigNtpSyncedChanged);

    m_connection->setNtpActive(false);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 1, m_waitTimeToEnterPolkitPassword);
    QCOMPARE(spyNtpActive.count(), 1);
    QCOMPARE(m_connection->getNtpActive(), false);

    // test side effects on other properties
    SignalSpyWaiter::waitForSignals(&spyNtpAvailable, 1, m_waitTimeNoPolkit);
    QCOMPARE(spyNtpAvailable.count(), 0);
    // Interesting: NTP off does not change NTP sync
    // We cross checked that with 'timedatectl set-ntp off' and 'timedatectl show'
    SignalSpyWaiter::waitForSignals(&spyNtpSynced, 1, m_waitTimeNoPolkit);
    QCOMPARE(spyNtpSynced.count(), 0);
}

void test_timedate1_connection::disableEnableNtp()
{
    QSignalSpy spyNtpAvailable(m_connection.get(), &Timedate1Connection::sigNtpAvailableChanged);
    QSignalSpy spyNtpActive(m_connection.get(), &Timedate1Connection::sigNtpActiveChanged);
    QSignalSpy spyNtpSynced(m_connection.get(), &Timedate1Connection::sigNtpSyncedChanged);

    m_connection->setNtpActive(false);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 1, m_waitTimeToEnterPolkitPassword);
    QCOMPARE(spyNtpActive.count(), 1);
    QCOMPARE(m_connection->getNtpActive(), false);

    m_connection->setNtpActive(true);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 2, m_waitTimeToEnterPolkitPassword);
    QCOMPARE(spyNtpActive.count(), 2);
    QCOMPARE(m_connection->getNtpActive(), true);

    // NTP on after off sets NTP sync off
    // We cross checked that with 'timedatectl set-ntp off' / 'timedatectl set-ntp on' / 'timedatectl show'
    QCOMPARE(spyNtpSynced.count(), 1);
    QCOMPARE(m_connection->getNtpSynced(), false);

    waitNtpSync();
    QCOMPARE(spyNtpSynced.count(), 2);
    QCOMPARE(m_connection->getNtpSynced(), true);

    // test side effects on other properties
    SignalSpyWaiter::waitForSignals(&spyNtpAvailable, 1, m_waitTimeNoPolkit);
    QCOMPARE(spyNtpAvailable.count(), 0);
}

void test_timedate1_connection::disableEnableNtpExternally()
{
    QSignalSpy spyNtpAvailable(m_connection.get(), &Timedate1Connection::sigNtpAvailableChanged);
    QSignalSpy spyNtpActive(m_connection.get(), &Timedate1Connection::sigNtpActiveChanged);
    QSignalSpy spyNtpSynced(m_connection.get(), &Timedate1Connection::sigNtpSyncedChanged);

    AbstractTimedate1ConnectionPtr externalConnection;
    setupConnection(externalConnection);
    QSignalSpy spyStartExternal(externalConnection.get(), &Timedate1Connection::sigAvailTimezonesChanged);
    externalConnection->start();
    SignalSpyWaiter::waitForSignals(&spyStartExternal, 1, m_waitTimeNoPolkit);
    QCOMPARE(spyStartExternal.count(), 1);

    externalConnection->setNtpActive(false);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 1, m_waitTimeToEnterPolkitPassword);
    QCOMPARE(spyNtpActive.count(), 1);
    QCOMPARE(m_connection->getNtpActive(), false);

    externalConnection->setNtpActive(true);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 2, m_waitTimeToEnterPolkitPassword);
    QCOMPARE(spyNtpActive.count(), 2);
    QCOMPARE(m_connection->getNtpActive(), true);

    // NTP on after off sets NTP sync off
    // We cross checked that with 'timedatectl set-ntp off' / 'timedatectl set-ntp on' / 'timedatectl show'
    QCOMPARE(spyNtpSynced.count(), 1);
    QCOMPARE(m_connection->getNtpSynced(), false);

    waitNtpSync();
    QCOMPARE(spyNtpSynced.count(), 2);
    QCOMPARE(m_connection->getNtpSynced(), true);

    // test side effects on other properties
    SignalSpyWaiter::waitForSignals(&spyNtpAvailable, 1, m_waitTimeNoPolkit);
    QCOMPARE(spyNtpAvailable.count(), 0);
}

void test_timedate1_connection::setNtpUnchangedCheckNotification()
{
    QSignalSpy spyNtpSet(m_connection.get(), &Timedate1Connection::sigNtpActiveSet);

    m_connection->setNtpActive(true);
    SignalSpyWaiter::waitForSignals(&spyNtpSet, 1, m_waitTimeToEnterPolkitPassword);
    QCOMPARE(spyNtpSet.count(), 1);
    QCOMPARE(spyNtpSet[0][0], true); // Howto test error???
}

void test_timedate1_connection::setNtpChangedCheckNotification()
{
    QSignalSpy spyNtpSet(m_connection.get(), &Timedate1Connection::sigNtpActiveSet);

    m_connection->setNtpActive(false);
    SignalSpyWaiter::waitForSignals(&spyNtpSet, 1, m_waitTimeToEnterPolkitPassword);
    QCOMPARE(spyNtpSet.count(), 1);
    QCOMPARE(spyNtpSet[0][0], true); // Howto test error???
}

void test_timedate1_connection::changeTimezoneValid()
{
    QSignalSpy spyTimezone(m_connection.get(), &Timedate1Connection::sigTimezoneChanged);
    QSignalSpy spyNtpAvailable(m_connection.get(), &Timedate1Connection::sigNtpAvailableChanged);
    QSignalSpy spyNtpActive(m_connection.get(), &Timedate1Connection::sigNtpActiveChanged);
    QSignalSpy spyNtpSynced(m_connection.get(), &Timedate1Connection::sigNtpSyncedChanged);

    const QString timezoneValid = "Etc/GMT+0";
    m_connection->setTimezone(timezoneValid);
    SignalSpyWaiter::waitForSignals(&spyTimezone, 1, m_waitTimeToEnterPolkitPassword);
    QCOMPARE(spyTimezone.count(), 1);
    QCOMPARE(m_connection->getTimeszone(), timezoneValid);

    // test side effects on other properties
    SignalSpyWaiter::waitForSignals(&spyNtpAvailable, 1, m_waitTimeNoPolkit);
    QCOMPARE(spyNtpAvailable.count(), 0);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 1, m_waitTimeNoPolkit);
    QCOMPARE(spyNtpActive.count(), 0);

    waitNtpSync();
    QCOMPARE(spyNtpSynced.count(), 0);
    QCOMPARE(m_connection->getNtpSynced(), true);
}

void test_timedate1_connection::changeTimezoneInvalid()
{
    QSignalSpy spyTimezone(m_connection.get(), &Timedate1Connection::sigTimezoneChanged);
    QSignalSpy spyNtpAvailable(m_connection.get(), &Timedate1Connection::sigNtpAvailableChanged);
    QSignalSpy spyNtpActive(m_connection.get(), &Timedate1Connection::sigNtpActiveChanged);
    QSignalSpy spyNtpSynced(m_connection.get(), &Timedate1Connection::sigNtpSyncedChanged);

    const QString timezoneInvalid = "Foo/Bar";
    m_connection->setTimezone(timezoneInvalid);
    SignalSpyWaiter::waitForSignals(&spyTimezone, 1, m_waitTimeNoPolkit); // we are not asked for password
    QCOMPARE(spyTimezone.count(), 0);
    QCOMPARE(m_connection->getTimeszone(), m_hostTimezone);

    // test side effects on other properties
    SignalSpyWaiter::waitForSignals(&spyNtpAvailable, 1, m_waitTimeNoPolkit);
    QCOMPARE(spyNtpAvailable.count(), 0);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 1, m_waitTimeNoPolkit);
    QCOMPARE(spyNtpActive.count(), 0);

    waitNtpSync();
    QCOMPARE(spyNtpSynced.count(), 0);
}

void test_timedate1_connection::changeTimezoneValidExternally()
{
    AbstractTimedate1ConnectionPtr externalConnection;
    setupConnection(externalConnection);
    QSignalSpy spyStartExternal(externalConnection.get(), &Timedate1Connection::sigAvailTimezonesChanged);
    externalConnection->start();
    SignalSpyWaiter::waitForSignals(&spyStartExternal, 1, m_waitTimeNoPolkit);
    QCOMPARE(spyStartExternal.count(), 1);

    QSignalSpy spyTimezoneInternal(m_connection.get(), &Timedate1Connection::sigTimezoneChanged);
    const QString timezoneValid = "Etc/GMT+0";
    externalConnection->setTimezone(timezoneValid);

    SignalSpyWaiter::waitForSignals(&spyTimezoneInternal, 1, m_waitTimeToEnterPolkitPassword);
    QCOMPARE(spyTimezoneInternal.count(), 1);
    QCOMPARE(m_connection->getTimeszone(), timezoneValid);
}

void test_timedate1_connection::changeTimezoneValidNotification()
{
    QSignalSpy spyTimezoneSet(m_connection.get(), &Timedate1Connection::sigTimezoneSet);

    const QString timezoneValid = "Etc/GMT+0";
    m_connection->setTimezone(timezoneValid);
    SignalSpyWaiter::waitForSignals(&spyTimezoneSet, 1, m_waitTimeToEnterPolkitPassword);
    QCOMPARE(spyTimezoneSet.count(), 1);
    QCOMPARE(spyTimezoneSet[0][0], true);
}

void test_timedate1_connection::changeTimezoneInvalidNotification()
{
    QSignalSpy spyTimezoneSet(m_connection.get(), &Timedate1Connection::sigTimezoneSet);

    const QString timezoneValid = "Foo";
    m_connection->setTimezone(timezoneValid);
    SignalSpyWaiter::waitForSignals(&spyTimezoneSet, 1, m_waitTimeToEnterPolkitPassword);
    QCOMPARE(spyTimezoneSet.count(), 1);
    QCOMPARE(spyTimezoneSet[0][0], false);
}

void test_timedate1_connection::changeTimeNtpOn()
{
    QSignalSpy spyDateTime(m_connection.get(), &Timedate1Connection::sigDateTimeSet);

    QDateTime testDateTime = QDateTime::fromString("2000-01-01 00:00:00", "yyyy-MM-dd HH:mm:ss");
    m_connection->setDateTime(testDateTime);
    SignalSpyWaiter::waitForSignals(&spyDateTime, 1, m_waitTimeToEnterPolkitPassword);
    QCOMPARE(spyDateTime.count(), 1);
    QCOMPARE(spyDateTime[0][0], false); // Set dateTime with NTP on is rejected
}

void test_timedate1_connection::changeTimeNtpOff()
{
    QSignalSpy spyDateTime(m_connection.get(), &Timedate1Connection::sigDateTimeSet);
    QSignalSpy spyNtpAvailable(m_connection.get(), &Timedate1Connection::sigNtpAvailableChanged);
    QSignalSpy spyNtpActive(m_connection.get(), &Timedate1Connection::sigNtpActiveChanged);
    QSignalSpy spyNtpSynced(m_connection.get(), &Timedate1Connection::sigNtpSyncedChanged);

    m_connection->setNtpActive(false);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 1, m_waitTimeToEnterPolkitPassword);
    QCOMPARE(spyNtpActive.count(), 1);
    spyNtpActive.clear();

    QDateTime testDateTime = QDateTime::fromString("2000-01-01 00:00:00", "yyyy-MM-dd HH:mm:ss");
    m_connection->setDateTime(testDateTime);
    SignalSpyWaiter::waitForSignals(&spyDateTime, 1, m_waitTimeToEnterPolkitPassword);
    QCOMPARE(spyDateTime.count(), 1);
    QCOMPARE(spyDateTime[0][0], true);

    // test side effects on other properties
    SignalSpyWaiter::waitForSignals(&spyNtpAvailable, 1, m_waitTimeNoPolkit);
    QCOMPARE(spyNtpAvailable.count(), 0);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 1, m_waitTimeNoPolkit);
    QCOMPARE(spyNtpActive.count(), 0);
    SignalSpyWaiter::waitForSignals(&spyNtpSynced, 1, m_waitTimeNoPolkit);
    QCOMPARE(spyNtpSynced.count(), 1);
    QCOMPARE(m_connection->getNtpSynced(), false);
}

void test_timedate1_connection::setupConnection(AbstractTimedate1ConnectionPtr &connection)
{
    QFETCH_GLOBAL(QString, testType);
    qInfo("Test type: %s", qPrintable(testType));
    if (testType == "Production") {
        m_ntpSyncMaxWaitMs = 10000;
        m_waitTimeToEnterPolkitPassword = 20000;
        m_waitTimeNoPolkit = 1000;
        connection = std::make_shared<Timedate1Connection>();
    }
    else {
        m_ntpSyncMaxWaitMs = 10;
        m_waitTimeToEnterPolkitPassword = 10;
        m_waitTimeNoPolkit = 10;
        connection = std::make_shared<TestTimedate1Connection>(m_ntpSyncMaxWaitMs);
    }
}

void test_timedate1_connection::waitNtpSync()
{
    QElapsedTimer timer;
    timer.start();
    qInfo("Wait NTP sync");
    QSignalSpy spySynced(m_connection.get(), &Timedate1Connection::sigNtpSyncedChanged);
    SignalSpyWaiter::waitForSignals(&spySynced, 1, m_ntpSyncMaxWaitMs);
    qInfo("Wait NTP sync complete after %llims", timer.elapsed());
}
