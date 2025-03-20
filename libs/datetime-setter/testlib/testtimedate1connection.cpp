#include "testtimedate1connection.h"
#include "testtimedate1storage.h"
#include "timezoneextractor.h"
#include <QFile>

TestTimedate1Connection::TestTimedate1Connection(int maxNtpSyncTimeoutMs) :
    m_ntpSyncOnDelay(maxNtpSyncTimeoutMs/2)
{
    setInitialTimezone(getDefaultTimezone());
    connect(&m_ntpSyncOnDelay, &TimerSingleShotQt::sigExpired,
            this, &TestTimedate1Connection::onSyncDelay);
}

void TestTimedate1Connection::setInitialTimezone(const QString &initialTimezone)
{
    TestTimedate1Storage::setInitialTimezone(initialTimezone);
}

const QString TestTimedate1Connection::getDefaultRegion()
{
    return TimezoneExtractor::extractRegion(getDefaultTimezone());
}

const QString TestTimedate1Connection::getDefaultCity()
{
    return TimezoneExtractor::extractCity(getDefaultTimezone());
}

void TestTimedate1Connection::start()
{
    Q_INIT_RESOURCE(datetime_setter_test);
    if (m_timezonesAvailable.isEmpty()) {
        QFile file("://available_timezones");
        if(file.open(QFile::ReadOnly)) {
            QString timezones = file.readAll();
            m_timezonesAvailable = timezones.split("\n", Qt::SkipEmptyParts);
            file.close();
        }
        connect(TestTimedate1Storage::getInstance(), &TestTimedate1Storage::sigNtpActiveChanged,
                this, &TestTimedate1Connection::onNtpActiveChange);
        connect(TestTimedate1Storage::getInstance(), &TestTimedate1Storage::sigTimezoneChanged,
                this, &TestTimedate1Connection::sigTimezoneChanged);
        QMetaObject::invokeMethod(this, "sigAvailTimezonesChanged", Qt::QueuedConnection);
        QMetaObject::invokeMethod(this, "sigStarted", Qt::QueuedConnection);
    }
}

const QStringList &TestTimedate1Connection::getAvailTimezones() const
{
    return m_timezonesAvailable;
}

QString TestTimedate1Connection::getTimeszone() const
{
    return TestTimedate1Storage::getInstance()->getTimezone();
}

void TestTimedate1Connection::setTimezone(const QString &timezone)
{
    if (m_timezonesAvailable.contains(timezone))
        TestTimedate1Storage::getInstance()->setTimezone(timezone);
}

bool TestTimedate1Connection::getNtpAvailable() const
{
    return m_ntpAvailable;
}

bool TestTimedate1Connection::getNtpSynced() const
{
    return m_ntpSynced;
}

bool TestTimedate1Connection::getNtpActive() const
{
    return TestTimedate1Storage::getInstance()->getNtpActive();
}

void TestTimedate1Connection::setNtpActive(bool active)
{
    if(active == TestTimedate1Storage::getInstance()->getNtpActive())
        return;
    TestTimedate1Storage::getInstance()->setNtpActive(active);
}

void TestTimedate1Connection::setDateTime(const QDateTime dateTime)
{
    // We have no tests / mock on valid datetime yet
    Q_UNUSED(dateTime)
    bool changeDateTimeOk = !TestTimedate1Storage::getInstance()->getNtpActive();
    QMetaObject::invokeMethod(this,
                              "sigDateTimeChanged",
                              Qt::QueuedConnection,
                              Q_ARG(bool, changeDateTimeOk));
    if (changeDateTimeOk) {
        m_ntpSynced = false;
        QMetaObject::invokeMethod(this, "sigNtpSyncedChanged", Qt::QueuedConnection);
    }
}

void TestTimedate1Connection::onSyncDelay()
{
    m_ntpSynced = true;
    QMetaObject::invokeMethod(this, "sigNtpSyncedChanged", Qt::QueuedConnection);
}

void TestTimedate1Connection::onNtpActiveChange()
{
    QMetaObject::invokeMethod(this, "sigNtpActiveChanged", Qt::QueuedConnection);
    bool active = TestTimedate1Storage::getInstance()->getNtpActive();
    if (active) {
        m_ntpSynced = false;
        QMetaObject::invokeMethod(this, "sigNtpSyncedChanged", Qt::QueuedConnection);
        m_ntpSyncOnDelay.start();
    }
}
