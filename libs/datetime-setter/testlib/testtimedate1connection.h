#ifndef TESTTIMEDATE1CONNECTION_H
#define TESTTIMEDATE1CONNECTION_H

#include "abstracttimedate1connection.h"
#include <timersingleshotqt.h>

class TestTimedate1Connection : public AbstractTimedate1Connection
{
    Q_OBJECT
public:
    TestTimedate1Connection();
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

private slots:
    void onSyncDelay();
private:
    QStringList m_timezonesAvailable;
    QString m_timezone = "Europe/Berlin";
    bool m_ntpAvailable = true;
    bool m_ntpSynced = true;
    bool m_ntpActive = true;
    TimerSingleShotQt m_ntpSyncOnDelay;
};

#endif // TESTTIMEDATE1CONNECTION_H
