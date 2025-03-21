#ifndef TIMEDATEFACADE_H
#define TIMEDATEFACADE_H

#include "abstracttimedate1connection.h"
#include <QObject>

class TimeDateFacade : public QObject
{
    Q_OBJECT
public:
    explicit TimeDateFacade();
    explicit TimeDateFacade(AbstractTimedate1ConnectionPtr timedateConnection);

    // convenience helper
    Q_INVOKABLE int maxDaysInYearMonth(int year, int month);

    Q_PROPERTY(bool ntpActive READ getNtpActive WRITE setNtpActive NOTIFY sigNtpActiveChanged FINAL)
    Q_SIGNAL void sigNtpActiveChanged();
    bool getNtpActive() const;
    void setNtpActive(bool active);

private:
    AbstractTimedate1ConnectionPtr m_timedateConnection;
};

#endif // TIMEDATEFACADE_H
