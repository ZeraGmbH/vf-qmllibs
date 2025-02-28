#ifndef ABSTRACTTIMEDATE1CONNECTION_H
#define ABSTRACTTIMEDATE1CONNECTION_H

#include <QObject>
#include <QStringList>
#include <QDateTime>

class AbstractTimedate1Connection : public QObject
{
    Q_OBJECT
public:
    virtual void start() = 0;

    virtual const QStringList &getAvailTimezones() const = 0;
    virtual QString getTimeszone() const = 0;
    virtual void setTimezone(const QString &timezone) = 0;

    virtual bool getNtpAvailable() const = 0;
    virtual bool getNtpSynced() const = 0;
    virtual bool getNtpActive() const = 0;
    virtual void setNtpActive(bool active) = 0;

    virtual void setDateTime(const QDateTime dateTime) = 0;
signals:
    void sigStarted();

    void sigAvailTimezonesChanged();
    void sigTimezoneChanged();

    void sigNtpAvailableChanged();
    void sigNtpSyncedChanged();
    void sigNtpActiveChanged();

    void sigDateTimeChanged(bool ok);
};

#endif // ABSTRACTTIMEDATE1CONNECTION_H
