#include "timedatefacade.h"
#include "timedate1connection.h"

TimeDateFacade::TimeDateFacade() :
    TimeDateFacade(std::make_shared<Timedate1Connection>())
{
    m_timedateConnection->start();
}

TimeDateFacade::TimeDateFacade(AbstractTimedate1ConnectionPtr timedateConnection) :
    m_timedateConnection(timedateConnection)
{
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigNtpActiveChanged,
            this, &TimeDateFacade::sigNtpActiveChanged);
}

int TimeDateFacade::maxDaysInYearMonth(int year, int month)
{
    QCalendar calendar;
    return calendar.daysInMonth(month, year);
}

bool TimeDateFacade::getNtpActive() const
{
    return m_timedateConnection->getNtpActive();
}

void TimeDateFacade::setNtpActive(bool active)
{
    m_timedateConnection->setNtpActive(active);
}
