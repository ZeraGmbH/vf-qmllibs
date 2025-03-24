#include "tasksettimezone.h"
#include <taskdecoratortimeout.h>

TaskTemplatePtr TaskSetTimezone::create(AbstractTimedate1ConnectionPtr timedateConnection,
                                        const QString &timezone,
                                        std::function<void ()> additionalErrorHandler, int timeoutMs)
{
    return TaskDecoratorTimeout::wrapTimeout(timeoutMs,
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
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigTimezoneSet, this, [=](bool ok) {
        finishTask(ok);
    });
    m_timedateConnection->setTimezone(m_timezone);
}
