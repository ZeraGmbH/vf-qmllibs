#include "testtimedate1storage.h"

QString TestTimedate1Storage::m_timezone;
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
        qInfo("Timezone changed to: '%s'", qPrintable(timezone));
        m_timezone = timezone;
        QMetaObject::invokeMethod(this, "sigTimezoneChanged", Qt::QueuedConnection);
    }
}

void TestTimedate1Storage::setInitialTimezone(const QString &timezone)
{
    m_timezone = timezone;
}
