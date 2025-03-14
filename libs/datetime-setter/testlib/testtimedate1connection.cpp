#include "testtimedate1connection.h"
#include "timezoneextractor.h"
#include <QFile>

TestTimedate1Connection::TestTimedate1Connection(int maxNtpSyncTimeoutMs) :
    m_ntpSyncOnDelay(maxNtpSyncTimeoutMs/2)
{
    connect(&m_ntpSyncOnDelay, &TimerSingleShotQt::sigExpired,
            this, &TestTimedate1Connection::onSyncDelay);
}

void TestTimedate1Connection::setInitialTimezone(const QString &initialTimezone)
{
    m_initialTimezone = initialTimezone;
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
    if(m_timezonesAvailable.isEmpty()) {
        QFile file("://available_timezones");
        if(file.open(QFile::ReadOnly)) {
            QString timezones = file.readAll();
            m_timezonesAvailable = timezones.split("\n", Qt::SkipEmptyParts);
            file.close();
        }
        QMetaObject::invokeMethod(this, "sigAvailTimezonesChanged", Qt::QueuedConnection);
        QMetaObject::invokeMethod(this, "sigStarted", Qt::QueuedConnection);
        m_timezone = m_initialTimezone;
    }
}

const QStringList &TestTimedate1Connection::getAvailTimezones() const
{
    return m_timezonesAvailable;
}

QString TestTimedate1Connection::getTimeszone() const
{
    return m_timezone;
}

void TestTimedate1Connection::setTimezone(const QString &timezone)
{
    if (m_timezonesAvailable.contains(timezone)) {
        m_timezone = timezone;
        QMetaObject::invokeMethod(this, "sigTimezoneChanged", Qt::QueuedConnection);
    }
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
    return m_ntpActive;
}

void TestTimedate1Connection::setNtpActive(bool active)
{
    if(active == m_ntpActive)
        return;
    m_ntpActive = active;
    QMetaObject::invokeMethod(this, "sigNtpActiveChanged", Qt::QueuedConnection);
    if(active) {
        m_ntpSynced = false;
        QMetaObject::invokeMethod(this, "sigNtpSyncedChanged", Qt::QueuedConnection);
        m_ntpSyncOnDelay.start();
    }
}

void TestTimedate1Connection::setDateTime(const QDateTime dateTime)
{
    // We have no tests / mock on valid datetime yet
    Q_UNUSED(dateTime)
    bool changeDateTimeOk = !m_ntpActive;
    QMetaObject::invokeMethod(this,
                              "sigDateTimeChanged",
                              Qt::QueuedConnection,
                              Q_ARG(bool, changeDateTimeOk));
    if(changeDateTimeOk) {
        m_ntpSynced = false;
        QMetaObject::invokeMethod(this, "sigNtpSyncedChanged", Qt::QueuedConnection);
    }
}

void TestTimedate1Connection::onSyncDelay()
{
    m_ntpSynced = true;
    QMetaObject::invokeMethod(this, "sigNtpSyncedChanged", Qt::QueuedConnection);
}
