#include "tasksettimezone.h"
#include <taskdecoratorerrorhandler.h>

TaskTemplatePtr TaskSetTimezone::create(AbstractTimedate1ConnectionPtr timedateConnection,
                                        const QString &timezone,
                                        std::function<void ()> additionalErrorHandler)
{
    return TaskDecoratorErrorHandler::create(
        std::make_unique<TaskSetTimezone>(timedateConnection, timezone),
        additionalErrorHandler);
}

TaskSetTimezone::TaskSetTimezone(AbstractTimedate1ConnectionPtr timedateConnection,
                                 const QString &timezone) :
    m_timedateConnection(timedateConnection),
    m_timezone(timezone)
{
}

void TaskSetTimezone::start()
{
    if(m_timezone == m_timedateConnection->getTimeszone()) {
        finishTaskQueued(true);
        return;
    }
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigTimezoneSet, this, [=](bool ok) {
        finishTask(ok);
    });
    m_timedateConnection->setTimezone(m_timezone);
}
