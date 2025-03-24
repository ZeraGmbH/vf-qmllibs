#ifndef TIMEDATEHELPER_H
#define TIMEDATEHELPER_H

#include "abstracttimedate1connection.h"
#include "tasktemplate.h"
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

    Q_INVOKABLE void setAllDateTime(const QString &timezone,
                                    bool ntpActive,
                                    int year, int month, int day,
                                    int hour, int minute, int second);
    Q_SIGNAL void sigAllDateTimeSet(QStringList errorMessages);
private:
    AbstractTimedate1ConnectionPtr m_timedateConnection;
    TaskTemplatePtr m_taskSetAll;
    std::shared_ptr<QStringList> m_errorMessages;
};

#endif // TIMEDATEHELPER_H
