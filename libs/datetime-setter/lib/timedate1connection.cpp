#include "timedate1connection.h"

static const char* dbusTimdate1Name = org::freedesktop::timedate1::staticInterfaceName();
static const char* dbusTimedate1Path = "/org/freedesktop/timedate1";
static QDBusConnection dbusSystemBus = QDBusConnection::systemBus();
static constexpr bool polkitInteractive = true;

Timedate1Connection::Timedate1Connection() :
    m_syncCheckTimer(200)
{
    dbusSystemBus.connect(
        dbusTimdate1Name,
        dbusTimedate1Path,
        "org.freedesktop.DBus.Properties",
        "PropertiesChanged",
        this,
        SLOT(onPropertiesChanged(QString, QVariantMap, QStringList))
        );
    // NTP synced
    // * is not directly caused by a setter
    // * does not seem supported in DBUS "PropertiesChanged". So add extra handling
    connect(&m_syncCheckTimer, &TimerPeriodicQt::sigExpired, this, [=](){
        updateNtpSynced(m_timedateInterface->nTPSynchronized());
    });
}

void Timedate1Connection::start()
{
    if (!m_timedateInterface) {
        m_timedateInterface = std::make_unique<org::freedesktop::timedate1>(
            dbusTimdate1Name,
            dbusTimedate1Path,
            dbusSystemBus);

        QDBusPendingReply<QStringList> reply = m_timedateInterface->ListTimezones();
        auto watcher = new QDBusPendingCallWatcher(reply, this);
        QObject::connect(watcher, &QDBusPendingCallWatcher::finished, this, [=]() {
            watcher->deleteLater();
            m_timezonesAvailable = reply.value();
            // At the time of writing:
            // * on our target 'Universal' is not reported by timedate1 but can be set and is
            //   default on first boot
            // * On build host 'Universal' is reported (just interesting: same for 'Etc/Universal')
            // * Our testlib/'available_timezones' contains both: 'Universal' and 'Etc/Universal'
            const QString initialTimezoneOnOurDeviceNotReportedByTimedate1 = "Universal";
            if (!m_timezonesAvailable.contains(initialTimezoneOnOurDeviceNotReportedByTimedate1))
                m_timezonesAvailable.append(initialTimezoneOnOurDeviceNotReportedByTimedate1);
            updateProperties();
            emit sigAvailTimezonesChanged();
            emit sigStarted();
            m_syncCheckTimer.start();
        });
    }
}

const QStringList &Timedate1Connection::getAvailTimezones() const
{
    return m_timezonesAvailable;
}

QString Timedate1Connection::getTimeszone() const
{
    return m_timezone;
}

void Timedate1Connection::setTimezone(const QString &timezone)
{
    m_timedateInterface->SetTimezone(timezone, polkitInteractive);
}

bool Timedate1Connection::getNtpAvailable() const
{
    return m_ntpAvailable;
}

bool Timedate1Connection::getNtpSynced() const
{
    return m_ntpSynced;
}

bool Timedate1Connection::getNtpActive() const
{
    return m_ntpActive;
}

void Timedate1Connection::setNtpActive(bool active)
{
    QDBusPendingReply<> reply = m_timedateInterface->SetNTP(active, polkitInteractive);
    auto watcher = new QDBusPendingCallWatcher(reply, this);
    QObject::connect(watcher, &QDBusPendingCallWatcher::finished, this, [=]() {
        updateProperties();
        watcher->deleteLater();
    });
}

void Timedate1Connection::setDateTime(const QDateTime dateTime)
{
    qlonglong usecUtc = dateTime.toMSecsSinceEpoch() * 1000;
    QDBusPendingReply<> reply = m_timedateInterface->SetTime(usecUtc, false, polkitInteractive);
    auto watcher = new QDBusPendingCallWatcher(reply, this);
    QObject::connect(watcher, &QDBusPendingCallWatcher::finished, this, [=]() {
        bool error = reply.isError();
        emit sigDateTimeChanged(!error);
        updateProperties();
        watcher->deleteLater();
    });
}

void Timedate1Connection::onPropertiesChanged(const QString &interface,
                                              const QVariantMap &changed_properties,
                                              const QStringList &invalidated_properties)
{
    if (interface == dbusTimdate1Name) {
        static const QString timezonProperty = "Timezone";
        if (changed_properties.contains(timezonProperty)) {
            const QString newTimezone = changed_properties[timezonProperty].toString();
            updateTimezone(newTimezone);
        }
    }
}

void Timedate1Connection::updateProperties()
{
    updateTimezone(m_timedateInterface->timezone());
    updateNtpAvailable(m_timedateInterface->canNTP());
    updateNtpSynced(m_timedateInterface->nTPSynchronized());
    updateNtpActive(m_timedateInterface->nTP());
}

void Timedate1Connection::updateTimezone(const QString &timezone)
{
    if (m_timezone != timezone) {
        if (!m_timezone.isEmpty())
            qInfo("Timezone changed to: '%s'", qPrintable(timezone));
        m_timezone = timezone;
        emit sigTimezoneChanged();
    }
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
    if (m_ntpActive != active) {
        m_ntpActive = active;
        emit sigNtpActiveChanged();
    }
}
