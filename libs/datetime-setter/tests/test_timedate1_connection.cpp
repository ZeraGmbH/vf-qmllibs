#include "test_timedate1_connection.h"
#include <qtestcase.h>
#include <signalspywaiter.h>
#include <QTest>

QTEST_MAIN(test_timedate1_connection)

constexpr int waitTimeToEnterPolkitPassword = 20000;
constexpr int waitTimeNoPolkit = 1000;
constexpr int waitTimeForSync = 20000;

void test_timedate1_connection::initTestCase()
{
    // Comment out for manual tests of Timedate1Connection
    // Be aware that this tests touches NTP/timezoe defaults!!!
    QSKIP("Skip: Won't work:\n* On OE there is no running timedate1\n* On dev-host: Polkit asks for granting access priviledges");
}

void test_timedate1_connection::init()
{
    m_connection = std::make_unique<Timedate1Connection>();
    QSignalSpy spyStart(m_connection.get(), &Timedate1Connection::sigAvailTimezonesChanged);
    m_connection->start();
    SignalSpyWaiter::waitForSignals(&spyStart, 1, waitTimeNoPolkit);
    QCOMPARE(spyStart.count(), 1);

    m_hostTimezone = m_connection->getTimeszone();

    // Make sure NTP is on and synced
    Q_ASSERT(m_connection->getNtpActive());
    Q_ASSERT(m_connection->getNtpSynced());
}

void test_timedate1_connection::cleanup()
{
    // Make sure tests leave with timezone entered and NTP on + synced
    if (!m_connection->getNtpActive()) {
        qInfo("Cleanup: Activate NTP");
        QSignalSpy spyNtpActive(m_connection.get(), &Timedate1Connection::sigNtpActiveChanged);
        m_connection->setNtpActive(true);
        SignalSpyWaiter::waitForSignals(&spyNtpActive, 1, waitTimeNoPolkit);
    }
    if (m_connection->getTimeszone() != m_hostTimezone) {
        qInfo("Cleanup: Restore timezone %s", qPrintable(m_hostTimezone));
        QSignalSpy spyTimezone(m_connection.get(), &Timedate1Connection::sigTimezoneChanged);
        m_connection->setTimezone(m_hostTimezone);
        SignalSpyWaiter::waitForSignals(&spyTimezone, 1, waitTimeNoPolkit);
    }
    if(!m_connection->getNtpSynced())
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
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 1, waitTimeToEnterPolkitPassword);
    QCOMPARE(spyNtpActive.count(), 1);
    QCOMPARE(m_connection->getNtpActive(), false);

    // test side effects on other properties
    SignalSpyWaiter::waitForSignals(&spyNtpAvailable, 1, waitTimeNoPolkit);
    QCOMPARE(spyNtpAvailable.count(), 0);
    // Interesting: NTP off does not change NTP sync
    // We cross checked that with 'timedatectl set-ntp off' and 'timedatectl show'
    SignalSpyWaiter::waitForSignals(&spyNtpSynced, 1, waitTimeNoPolkit);
    QCOMPARE(spyNtpSynced.count(), 0);
}

void test_timedate1_connection::disableEnableNtp()
{
    QSignalSpy spyNtpAvailable(m_connection.get(), &Timedate1Connection::sigNtpAvailableChanged);
    QSignalSpy spyNtpActive(m_connection.get(), &Timedate1Connection::sigNtpActiveChanged);
    QSignalSpy spyNtpSynced(m_connection.get(), &Timedate1Connection::sigNtpSyncedChanged);

    m_connection->setNtpActive(false);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 1, waitTimeToEnterPolkitPassword);
    QCOMPARE(spyNtpActive.count(), 1);
    QCOMPARE(m_connection->getNtpActive(), false);

    m_connection->setNtpActive(true);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 2, waitTimeToEnterPolkitPassword);
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
    SignalSpyWaiter::waitForSignals(&spyNtpAvailable, 1, waitTimeNoPolkit);
    QCOMPARE(spyNtpAvailable.count(), 0);

}

void test_timedate1_connection::changeTimezoneValid()
{
    QSignalSpy spyTimezone(m_connection.get(), &Timedate1Connection::sigTimezoneChanged);
    QSignalSpy spyNtpAvailable(m_connection.get(), &Timedate1Connection::sigNtpAvailableChanged);
    QSignalSpy spyNtpActive(m_connection.get(), &Timedate1Connection::sigNtpActiveChanged);
    QSignalSpy spyNtpSynced(m_connection.get(), &Timedate1Connection::sigNtpSyncedChanged);

    const QString timezoneValid = "Etc/GMT+0";
    m_connection->setTimezone(timezoneValid);
    SignalSpyWaiter::waitForSignals(&spyTimezone, 1, waitTimeToEnterPolkitPassword);
    QCOMPARE(spyTimezone.count(), 1);
    QCOMPARE(m_connection->getTimeszone(), timezoneValid);

    // test side effects on other properties
    SignalSpyWaiter::waitForSignals(&spyNtpAvailable, 1, waitTimeNoPolkit);
    QCOMPARE(spyNtpAvailable.count(), 0);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 1, waitTimeNoPolkit);
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
    SignalSpyWaiter::waitForSignals(&spyTimezone, 1, waitTimeNoPolkit); // we are not asked for password
    QCOMPARE(spyTimezone.count(), 0);
    QCOMPARE(m_connection->getTimeszone(), m_hostTimezone);

    // test side effects on other properties
    SignalSpyWaiter::waitForSignals(&spyNtpAvailable, 1, waitTimeNoPolkit);
    QCOMPARE(spyNtpAvailable.count(), 0);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 1, waitTimeNoPolkit);
    QCOMPARE(spyNtpActive.count(), 0);

    waitNtpSync();
    QCOMPARE(spyNtpSynced.count(), 0);
}

void test_timedate1_connection::changeTimeNtpOn()
{
    QSignalSpy spyDateTime(m_connection.get(), &Timedate1Connection::sigDateTimeChanged);

    QDateTime testDateTime = QDateTime::fromString("2000-01-01 00:00:00", "yyyy-MM-dd HH:mm:ss");
    m_connection->setDateTime(testDateTime);
    SignalSpyWaiter::waitForSignals(&spyDateTime, 1, waitTimeToEnterPolkitPassword);
    QCOMPARE(spyDateTime.count(), 1);
    QCOMPARE(spyDateTime[0][0], false); // Set dateTime with NTP on is rejected
}

void test_timedate1_connection::changeTimeNtpOff()
{
    QSignalSpy spyDateTime(m_connection.get(), &Timedate1Connection::sigDateTimeChanged);
    QSignalSpy spyNtpAvailable(m_connection.get(), &Timedate1Connection::sigNtpAvailableChanged);
    QSignalSpy spyNtpActive(m_connection.get(), &Timedate1Connection::sigNtpActiveChanged);
    QSignalSpy spyNtpSynced(m_connection.get(), &Timedate1Connection::sigNtpSyncedChanged);

    m_connection->setNtpActive(false);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 1, waitTimeToEnterPolkitPassword);
    QCOMPARE(spyNtpActive.count(), 1);
    spyNtpActive.clear();

    QDateTime testDateTime = QDateTime::fromString("2000-01-01 00:00:00", "yyyy-MM-dd HH:mm:ss");
    m_connection->setDateTime(testDateTime);
    SignalSpyWaiter::waitForSignals(&spyDateTime, 1, waitTimeToEnterPolkitPassword);
    QCOMPARE(spyDateTime.count(), 1);
    QCOMPARE(spyDateTime[0][0], true);

    // test side effects on other properties
    SignalSpyWaiter::waitForSignals(&spyNtpAvailable, 1, waitTimeNoPolkit);
    QCOMPARE(spyNtpAvailable.count(), 0);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 1, waitTimeNoPolkit);
    QCOMPARE(spyNtpActive.count(), 0);
    SignalSpyWaiter::waitForSignals(&spyNtpSynced, 1, waitTimeNoPolkit);
    QCOMPARE(spyNtpSynced.count(), 1);
    QCOMPARE(m_connection->getNtpSynced(), false);
}

void test_timedate1_connection::waitNtpSync()
{
    QElapsedTimer timer;
    timer.start();
    qInfo("Wait NTP sync");
    QSignalSpy spySynced(m_connection.get(), &Timedate1Connection::sigNtpSyncedChanged);
    SignalSpyWaiter::waitForSignals(&spySynced, 1, waitTimeForSync);
    qInfo("Wait NTP sync complete after %llims", timer.elapsed());
}
