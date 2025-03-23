#ifndef TIMEDATEHELPER_H
#define TIMEDATEHELPER_H

#include "abstracttimedate1connection.h"
#include <QObject>

class TimeDateHelper : public QObject
{
    Q_OBJECT
public:
    explicit TimeDateHelper();
    explicit TimeDateHelper(AbstractTimedate1ConnectionPtr timedateConnection);

    // convenience helper
    Q_INVOKABLE int maxDaysInYearMonth(int year, int month);

    Q_PROPERTY(bool ntpActive READ getNtpActive NOTIFY sigNtpActiveChanged FINAL)
    Q_SIGNAL void sigNtpActiveChanged();
    bool getNtpActive() const;

private:
    AbstractTimedate1ConnectionPtr m_timedateConnection;
};

#endif // TIMEDATEHELPER_H
