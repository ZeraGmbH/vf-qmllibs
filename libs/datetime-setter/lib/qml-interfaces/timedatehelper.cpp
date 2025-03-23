#include "timedatehelper.h"
#include "timedate1connection.h"

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
