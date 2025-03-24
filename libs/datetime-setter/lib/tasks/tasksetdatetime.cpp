#include "tasksetdatetime.h"
#include <taskdecoratortimeout.h>
#include <QDateTime>

TaskTemplatePtr TaskSetDateTime::create(AbstractTimedate1ConnectionPtr timedateConnection,
                                        QDateTime datetime,
                                        std::function<void ()> additionalErrorHandler, int timeoutMs)
{
    return TaskDecoratorTimeout::wrapTimeout(timeoutMs,
                                             std::make_unique<TaskSetDateTime>(timedateConnection, datetime),
                                             additionalErrorHandler);
}

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
