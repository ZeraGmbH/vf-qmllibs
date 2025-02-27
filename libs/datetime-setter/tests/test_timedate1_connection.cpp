#include "test_timedate1_connection.h"
#include <qtestcase.h>
#include <signalspywaiter.h>
#include <QTest>

QTEST_MAIN(test_timedate1_connection)

void test_timedate1_connection::initTestCase()
{
    // Comment out for manual tests of Timedate1Connection
    // Be aware that this tests touches NTP/timezoe defaults!!!
    QSKIP("Skip: Won't work:\n* On OE there is no running timedate1\n* On dev-host: Polkit asks for granting access priviledges");
}

void test_timedate1_connection::init()
{
    m_connection = std::make_unique<Timedate1Connection>();
    QSignalSpy spy(m_connection.get(), &Timedate1Connection::sigAvailTimezonesChanged);
    m_connection->start();
    SignalSpyWaiter::waitForSignals(&spy, 1);
    QCOMPARE(spy.count(), 1);
}

void test_timedate1_connection::cleanup()
{
    m_connection.reset();
}

void test_timedate1_connection::availableTimezones()
{
    QStringList availTimezones = m_connection->getAvailTimezones();
    QVERIFY(!availTimezones.isEmpty());
    qInfo("%s", qPrintable(availTimezones.join("\n")));
}

void test_timedate1_connection::enableDisableNtp()
{
    bool hostNtpActive = m_connection->getNtpActive();
    QSignalSpy spyNtpAvailable(m_connection.get(), &Timedate1Connection::sigNtpAvailableChanged);
    QSignalSpy spyNtpActive(m_connection.get(), &Timedate1Connection::sigNtpActiveChanged);
    QSignalSpy spyNtpSynced(m_connection.get(), &Timedate1Connection::sigNtpSyncedChanged);

    m_connection->setNtpActive(!hostNtpActive);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 1, 20000); // polkit
    QCOMPARE(spyNtpActive.count(), 1);
    QCOMPARE(m_connection->getNtpActive(), !hostNtpActive);

    m_connection->setNtpActive(hostNtpActive);
    SignalSpyWaiter::waitForSignals(&spyNtpActive, 2, 1000);
    QCOMPARE(spyNtpActive.count(), 2);
    QCOMPARE(m_connection->getNtpActive(), hostNtpActive);

    // test side effects on other properties
    QCOMPARE(spyNtpAvailable.count(), 0);
    // Interesting: NTP off does not change NTP sync
    // We cross checked that with 'timedatectl set-ntp off' and 'timedatectl show'
    QCOMPARE(spyNtpSynced.count(), 0);
}

void test_timedate1_connection::changeTimezone()
{
    const QString hostTimezone = m_connection->getTimeszone();
    QSignalSpy spyTimezone(m_connection.get(), &Timedate1Connection::sigTimezoneChanged);
    QSignalSpy spyNtpAvailable(m_connection.get(), &Timedate1Connection::sigNtpAvailableChanged);
    QSignalSpy spyNtpActive(m_connection.get(), &Timedate1Connection::sigNtpActiveChanged);
    QSignalSpy spyNtpSynced(m_connection.get(), &Timedate1Connection::sigNtpSyncedChanged);

    const QString timezoneValid = "Etc/GMT+0";
    m_connection->setTimezone(timezoneValid);
    SignalSpyWaiter::waitForSignals(&spyTimezone, 1, 20000); // polkit
    QCOMPARE(spyTimezone.count(), 1);
    QCOMPARE(m_connection->getTimeszone(), timezoneValid);

    m_connection->setTimezone(hostTimezone);
    SignalSpyWaiter::waitForSignals(&spyTimezone, 2, 1000);
    QCOMPARE(spyTimezone.count(), 2);
    QCOMPARE(m_connection->getTimeszone(), hostTimezone);

    const QString timezoneInvalid = "Foo/Bar";
    m_connection->setTimezone(timezoneInvalid);
    SignalSpyWaiter::waitForSignals(&spyTimezone, 3, 1000);
    QCOMPARE(spyTimezone.count(), 2);
    QCOMPARE(m_connection->getTimeszone(), hostTimezone);

    // test side effects on other properties
    QCOMPARE(spyNtpAvailable.count(), 0);
    QCOMPARE(spyNtpActive.count(), 0);
    QCOMPARE(spyNtpSynced.count(), 0);
}
