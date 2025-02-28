#ifndef TIMEDATE1CONNECTION_H
#define TIMEDATE1CONNECTION_H

#include "abstracttimedate1connection.h"
#include "timedate1interface.h"
#include <timerperiodicqt.h>

class Timedate1Connection : public AbstractTimedate1Connection
{
    Q_OBJECT
public:
    Timedate1Connection();
    void start() override;
    int getNtpSyncMsMax() const override;

    const QStringList &getAvailTimezones() const override;
    QString getTimeszone() const override;
    void setTimezone(const QString &timezone) override;

    bool getNtpAvailable() const override;
    bool getNtpSynced() const override;
    bool getNtpActive() const override;
    void setNtpActive(bool active) override;

    void setDateTime(const QDateTime dateTime) override;

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
