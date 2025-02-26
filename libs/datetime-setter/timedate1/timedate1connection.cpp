#include "timedate1connection.h"

void Timedate1Connection::start()
{
    if (!m_timedateInterface) {
        m_timedateInterface = std::make_unique<org::freedesktop::timedate1>(
            org::freedesktop::timedate1::staticInterfaceName(),
            "/org/freedesktop/timedate1",
            QDBusConnection::systemBus());

        QDBusPendingReply<QStringList> reply = m_timedateInterface->ListTimezones();
        auto watcher = new QDBusPendingCallWatcher(reply, this);
        QObject::connect(watcher, &QDBusPendingCallWatcher::finished, this, [=]() {
            watcher->deleteLater();
            m_timezonesAvailable = reply.value();
            emit sigAvailTimezonesChanged();
            updateProperties();
        });
    }
}

const QStringList &Timedate1Connection::getAvailTimezones() const
{
    return m_timezonesAvailable;
}

bool Timedate1Connection::getNtpAvailable() const
{
    return m_ntpAvailable;
}

bool Timedate1Connection::getNtpSynced() const
{
    return m_ntpSynced;
}

void Timedate1Connection::updateProperties()
{
    const bool newCanNtp = m_timedateInterface->canNTP();
    if (m_ntpAvailable != newCanNtp) {
        m_ntpAvailable = newCanNtp;
        emit sigCanNtpChanged();
    }

    const bool newIsNtpSynced = m_timedateInterface->nTPSynchronized();
    if (m_ntpSynced != newIsNtpSynced) {
        m_ntpSynced = newIsNtpSynced;
        emit sigIsNtpSyncedChanged();
    }
}
