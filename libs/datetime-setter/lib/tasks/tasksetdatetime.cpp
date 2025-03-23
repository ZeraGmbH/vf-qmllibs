#include "tasksetdatetime.h"
#include <QDateTime>

TaskSetDateTime::TaskSetDateTime(AbstractTimedate1ConnectionPtr timedateConnection,
                                 QDateTime datetime) :
    m_timedateConnection(timedateConnection),
    m_datetime(datetime)
{
}

void TaskSetDateTime::start()
{
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigDateTimeSet, this, [=](bool ok) {
        finishTask(ok);
    });
    m_timedateConnection->setDateTime(m_datetime);
}
