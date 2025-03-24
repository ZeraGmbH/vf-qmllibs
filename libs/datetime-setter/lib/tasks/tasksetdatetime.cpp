#include "tasksetdatetime.h"
#include <taskdecoratorerrorhandler.h>

TaskTemplatePtr TaskSetDateTime::create(AbstractTimedate1ConnectionPtr timedateConnection,
                                        QDateTime datetime,
                                        std::function<void ()> additionalErrorHandler)
{
    return TaskDecoratorErrorHandler::create(
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
