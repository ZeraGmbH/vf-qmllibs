#ifndef TIMEDATE1CONNECTION_H
#define TIMEDATE1CONNECTION_H

#include "timedate1interface.h"
#include <timerperiodicqt.h>
#include <QStringList>
#include <QVariantMap>
#include <QDateTime>

class Timedate1Connection : public QObject
{
    Q_OBJECT
public:
    Timedate1Connection();
    void start();

    const QStringList &getAvailTimezones() const;
    QString getTimeszone() const;
    void setTimezone(const QString &timezone);

    bool getNtpAvailable() const;
    bool getNtpSynced() const;
    bool getNtpActive() const;
    void setNtpActive(bool active);

    void setDateTime(const QDateTime dateTime);
signals:
    void sigStarted();

    void sigAvailTimezonesChanged();
    void sigTimezoneChanged();

    void sigNtpAvailableChanged();
    void sigNtpSyncedChanged();
    void sigNtpActiveChanged();

    void sigDateTimeChanged(bool ok);

private:
    void updateProperties();
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
    TimerPeriodicQt m_syncCheckTimer;
};

#endif // TIMEDATE1CONNECTION_H
