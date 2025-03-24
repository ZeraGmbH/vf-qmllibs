#include "timedatehelper.h"
#include "timedate1connection.h"
#include "tasksetalldatetime.h"
#include <QDateTime>

TimeDateHelper::TimeDateHelper() :
    TimeDateHelper(std::make_shared<Timedate1Connection>())
{
    m_timedateConnection->start();
}

TimeDateHelper::TimeDateHelper(AbstractTimedate1ConnectionPtr timedateConnection) :
    m_timedateConnection(timedateConnection)
{
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigNtpActiveChanged,
            this, &TimeDateHelper::sigNtpActiveChanged);
}

int TimeDateHelper::maxDaysInYearMonth(int year, int month)
{
    QCalendar calendar;
    return calendar.daysInMonth(month, year);
}

bool TimeDateHelper::getNtpActive() const
{
    return m_timedateConnection->getNtpActive();
}

void TimeDateHelper::setAllDateTime(const QString &timezone,
                                    bool ntpActive,
                                    int year, int month, int day,
                                    int hour, int minute, int second)
{
    QDateTime dateTime(QDate(year, month, day), QTime(hour, minute, second));
    m_errorMessages = std::make_shared<QStringList>();
    m_taskSetAll = TaskSetAllDateTime::create(m_timedateConnection,
                                              timezone, ntpActive, dateTime,
                                              m_errorMessages);
    connect(m_taskSetAll.get(), &TaskTemplate::sigFinish, this, [=]() {
        emit sigAllDateTimeSet(*m_errorMessages);
    });
    m_taskSetAll->start();
}
