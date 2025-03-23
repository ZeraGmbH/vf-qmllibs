#include "tasksettimezone.h"

TaskSetTimezone::TaskSetTimezone(AbstractTimedate1ConnectionPtr timedateConnection,
                                 const QString &timezone) :
    m_timedateConnection(timedateConnection),
    m_timezone(timezone)
{
}

void TaskSetTimezone::start()
{
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigTimezoneSet, this, [=](bool ok) {
        finishTask(ok);
    });
    m_timedateConnection->setTimezone(m_timezone);
}
