#include "timedate1connection.h"

Timedate1Connection::Timedate1Connection()
{
}

void Timedate1Connection::connectDbus()
{
    m_timedateInterface = std::make_unique<org::freedesktop::timedate1>(
        org::freedesktop::timedate1::staticInterfaceName(),
        "/org/freedesktop/timedate1",
        QDBusConnection::systemBus());
    QStringList timezones = m_timedateInterface->ListTimezones().value();
    Q_ASSERT(!timezones.isEmpty());
}

