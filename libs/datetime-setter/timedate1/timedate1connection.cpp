#include "timedate1connection.h"

static const char* dbusTimdate1Name = org::freedesktop::timedate1::staticInterfaceName();
static const char* dbusTimedate1Path = "/org/freedesktop/timedate1";
static QDBusConnection dbusSystemBus = QDBusConnection::systemBus();

void Timedate1Connection::start()
{
    if (!m_timedateInterface) {
        m_timedateInterface = std::make_unique<org::freedesktop::timedate1>(
            dbusTimdate1Name,
            dbusTimedate1Path,
            dbusSystemBus);

        dbusSystemBus.connect(
            dbusTimdate1Name,
            dbusTimedate1Path,
            "org.freedesktop.DBus.Properties",
            "PropertiesChanged",
            this,
            SLOT(onPropertiesChanged(QString, QVariantMap, QStringList)) // Qt5 connection not supported
            );

        QDBusPendingReply<QStringList> reply = m_timedateInterface->ListTimezones();
        auto watcher = new QDBusPendingCallWatcher(reply, this);
        QObject::connect(watcher, &QDBusPendingCallWatcher::finished, this, [=]() {
            watcher->deleteLater();
            m_timezonesAvailable = reply.value();
            emit sigAvailTimezonesChanged();
            initProperties();
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

void Timedate1Connection::onPropertiesChanged(const QString &interface,
                                              const QVariantMap &changedProperties,
                                              const QStringList &invalidatedProperties)
{
    Q_UNUSED(invalidatedProperties)
    if (interface == dbusTimdate1Name) {
        auto iterNtpAvailable = changedProperties.constFind("CanNTP");
        if(iterNtpAvailable != changedProperties.constEnd())
            updateNtpAvailable(iterNtpAvailable.value().toBool());

        auto iterNtpSynced = changedProperties.constFind("NTPSynchronized");
        if(iterNtpSynced != changedProperties.constEnd())
            updateNtpSynced(iterNtpSynced.value().toBool());

        auto iterNtpActive = changedProperties.constFind("NTP");
        if(iterNtpActive != changedProperties.constEnd())
            updateNtpActive(iterNtpActive.value().toBool());
    }
}

void Timedate1Connection::initProperties()
{
    updateNtpAvailable(m_timedateInterface->canNTP());
    updateNtpSynced(m_timedateInterface->nTPSynchronized());
    updateNtpActive(m_timedateInterface->nTP());
}

void Timedate1Connection::updateNtpAvailable(bool available)
{
    if (m_ntpAvailable != available) {
        m_ntpAvailable = available;
        emit sigNtpAvailableChanged();
    }
}

void Timedate1Connection::updateNtpSynced(bool synced)
{
    if (m_ntpSynced != synced) {
        m_ntpSynced = synced;
        emit sigNtpSyncedChanged();
    }
}

void Timedate1Connection::updateNtpActive(bool active)
{
    if(m_ntpActive != active) {
        m_ntpActive = active;
        emit sigNtpActiveChanged();
    }
}
