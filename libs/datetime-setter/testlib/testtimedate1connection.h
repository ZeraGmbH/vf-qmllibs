#ifndef TESTTIMEDATE1CONNECTION_H
#define TESTTIMEDATE1CONNECTION_H

#include "abstracttimedate1connection.h"
#include <timersingleshotqt.h>
#include <QDateTime>

class TestTimedate1Connection : public AbstractTimedate1Connection
{
    Q_OBJECT
public:
    static void setCanNtp(bool on); // once we find a way to disable canNTP on production, this has to go
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

    QDateTime getDateTimeSetSuccessfully() const;

private slots:
    void onSyncDelay();
    void onNtpActiveChange();
private:
    QStringList m_timezonesAvailable;
    bool m_ntpAvailable = true;
    bool m_ntpSynced = true;
    TimerSingleShotQt m_ntpSyncOnDelay;
    QDateTime m_dateTimeSetSuccessfully;
    static bool m_canNtp;
};

#endif // TESTTIMEDATE1CONNECTION_H
