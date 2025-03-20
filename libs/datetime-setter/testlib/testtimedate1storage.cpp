#include "testtimedate1storage.h"

QString TestTimedate1Storage::m_timezone;
bool TestTimedate1Storage::m_ntpActive = true;
TestTimedate1Storage* TestTimedate1Storage::m_instance = nullptr;

TestTimedate1Storage *TestTimedate1Storage::getInstance()
{
    if(!m_instance)
        m_instance = new TestTimedate1Storage;
    return m_instance;
}

QString TestTimedate1Storage::getTimezone() const
{
    return m_timezone;
}

void TestTimedate1Storage::setTimezone(const QString &timezone)
{
    if (m_timezone != timezone) {
        m_timezone = timezone;
        qInfo("Timezone changed to: '%s'", qPrintable(timezone));
        QMetaObject::invokeMethod(this, "sigTimezoneChanged", Qt::QueuedConnection);
    }
}

void TestTimedate1Storage::setInitialTimezone(const QString &timezone)
{
    m_timezone = timezone;
}

bool TestTimedate1Storage::getNtpActive() const
{
    return m_ntpActive;
}

void TestTimedate1Storage::setNtpActive(bool active)
{
    if(m_ntpActive != active) {
        m_ntpActive = active;
        QMetaObject::invokeMethod(this, "sigNtpActiveChanged", Qt::QueuedConnection);
    }
}
