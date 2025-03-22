#ifndef ABSTRACTTIMEDATE1CONNECTION_H
#define ABSTRACTTIMEDATE1CONNECTION_H

#include <QObject>
#include <QStringList>
#include <QDateTime>
#include <memory>

class AbstractTimedate1Connection : public QObject
{
    Q_OBJECT
public:
    virtual void start() = 0;
    Q_SIGNAL void sigStarted();

    virtual const QStringList &getAvailTimezones() const = 0;
    Q_SIGNAL void sigAvailTimezonesChanged();

    virtual QString getTimeszone() const = 0;
    virtual void setTimezone(const QString &timezone) = 0;
    Q_SIGNAL void sigTimezoneChanged();
    Q_SIGNAL void sigTimezoneSet(bool ok);

    virtual bool getNtpAvailable() const = 0;
    Q_SIGNAL void sigNtpAvailableChanged();

    virtual bool getNtpSynced() const = 0;
    Q_SIGNAL void sigNtpSyncedChanged();

    virtual bool getNtpActive() const = 0;
    virtual void setNtpActive(bool active) = 0;
    Q_SIGNAL void sigNtpActiveChanged();
    Q_SIGNAL void sigNtpActiveSet(bool ok);

    virtual void setDateTime(const QDateTime dateTime) = 0;
    Q_SIGNAL void sigDateTimeSet(bool ok);
};

typedef std::shared_ptr<AbstractTimedate1Connection> AbstractTimedate1ConnectionPtr;

#endif // ABSTRACTTIMEDATE1CONNECTION_H
