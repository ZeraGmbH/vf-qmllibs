#ifndef TESTTIMEDATE1CONNECTION_H
#define TESTTIMEDATE1CONNECTION_H

#include "abstracttimedate1connection.h"
#include <timersingleshotqt.h>

class TestTimedate1Connection : public AbstractTimedate1Connection
{
    Q_OBJECT
public:
    TestTimedate1Connection(int maxNtpSyncTimeoutMs);

    void setInitialTimezone(const QString &initialTimezone);
    static const QString getDefaultTimezone() { return "Europe/Berlin"; }
    static const QString getDefaultRegion();
    static const QString getDefaultCity();

    void start() override;

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
    bool m_ntpAvailable = true;
    bool m_ntpSynced = true;
    bool m_ntpActive = true;
    TimerSingleShotQt m_ntpSyncOnDelay;
};

#endif // TESTTIMEDATE1CONNECTION_H
