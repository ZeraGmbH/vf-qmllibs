#ifndef TIMEDATE1CONNECTION_H
#define TIMEDATE1CONNECTION_H

#include "timedate1interface.h"

class Timedate1Connection : public QObject
{
    Q_OBJECT
public:
    void start();

    const QStringList &getAvailTimezones() const;
    bool getNtpAvailable() const ;
    bool getNtpSynced() const;
signals:
    void sigAvailTimezonesChanged();
    void sigCanNtpChanged();
    void sigIsNtpSyncedChanged();

private:
    void updateProperties();
    std::unique_ptr<org::freedesktop::timedate1> m_timedateInterface;
    QStringList m_timezonesAvailable;
    bool m_ntpAvailable = false;
    bool m_ntpSynced = false;
};

#endif // TIMEDATE1CONNECTION_H
