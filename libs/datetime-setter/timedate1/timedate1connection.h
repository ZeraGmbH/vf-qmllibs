#ifndef TIMEDATE1CONNECTION_H
#define TIMEDATE1CONNECTION_H

#include "timedate1interface.h"
#include <QStringList>
#include <QVariantMap>

class Timedate1Connection : public QObject
{
    Q_OBJECT
public:
    void start();

    const QStringList &getAvailTimezones() const;
    QString getTimeszone() const;
    void setTimezone(const QString &timezone);

    bool getNtpAvailable() const;
    bool getNtpSynced() const;
    bool getNtpActive() const;
    void setNtpActive(bool active);
signals:
    void sigStarted();
    void sigAvailTimezonesChanged();
    void sigTimezoneChanged();
    void sigNtpAvailableChanged();
    void sigNtpSyncedChanged();
    void sigNtpActiveChanged();

private slots:
    void onPropertiesChanged(const QString &interface,
                             const QVariantMap &changedProperties,
                             const QStringList &invalidatedProperties);
private:
    void initProperties();
    void updateTimezone(const QString &timezone);
    void updateNtpAvailable(bool available);
    void updateNtpSynced(bool synced);
    void updateNtpActive(bool active);

    std::unique_ptr<org::freedesktop::timedate1> m_timedateInterface;
    QStringList m_timezonesAvailable;
    QString m_timezone;
    bool m_ntpAvailable = false;
    bool m_ntpSynced = false;
    bool m_ntpActive = false;
};

#endif // TIMEDATE1CONNECTION_H
