#include "timedatefacade.h"
#include "timedate1connection.h"

TimeDateFacade::TimeDateFacade() :
    TimeDateFacade(std::make_shared<Timedate1Connection>())
{
}

TimeDateFacade::TimeDateFacade(AbstractTimedate1ConnectionPtr timedateConnection) :
    m_timedateConnection(timedateConnection)
{
}

int TimeDateFacade::maxDaysInYearMonth(int year, int month)
{
    QCalendar calendar;
    return calendar.daysInMonth(month, year);
}
