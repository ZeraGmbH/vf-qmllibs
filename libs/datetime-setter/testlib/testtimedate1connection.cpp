#include "testtimedate1connection.h"
#include "testtimedate1storage.h"
#include "timezoneextractor.h"
#include <QFile>

bool TestTimedate1Connection::m_canNtp = true;

void TestTimedate1Connection::setCanNtp(bool on)
{
    m_canNtp = on;
}

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
        if (file.open(QFile::ReadOnly)) {
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
    bool ok = m_timezonesAvailable.contains(timezone);
    if (ok)
        TestTimedate1Storage::getInstance()->setTimezone(timezone);
    QMetaObject::invokeMethod(this,
                              "sigTimezoneSet",
                              Qt::QueuedConnection,
                              Q_ARG(bool, ok));
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
    if (m_canNtp && active != TestTimedate1Storage::getInstance()->getNtpActive())
        TestTimedate1Storage::getInstance()->setNtpActive(active);
    QMetaObject::invokeMethod(this,
                              "sigNtpActiveSet",
                              Qt::QueuedConnection,
                              Q_ARG(bool, m_canNtp));
}

void TestTimedate1Connection::setDateTime(const QDateTime dateTime)
{
    bool changeDateTimeOk = dateTime.isValid() && !TestTimedate1Storage::getInstance()->getNtpActive();
    if(changeDateTimeOk)
        m_dateTimeSetSuccessfully = dateTime;
    QMetaObject::invokeMethod(this,
                              "sigDateTimeSet",
                              Qt::QueuedConnection,
                              Q_ARG(bool, changeDateTimeOk));
    if (changeDateTimeOk) {
        m_ntpSynced = false;
        QMetaObject::invokeMethod(this, "sigNtpSyncedChanged", Qt::QueuedConnection);
    }
}

QDateTime TestTimedate1Connection::getDateTimeSetSuccessfully() const
{
    return m_dateTimeSetSuccessfully;
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
