#include "taskwaitntp.h"
#include <taskdecoratorerrorhandler.h>

TaskTemplatePtr TaskWaitNtp::create(AbstractTimedate1ConnectionPtr timedateConnection,
                                    bool ntpActiveSettled,
                                    std::function<void ()> additionalErrorHandler)
{
    return TaskDecoratorErrorHandler::create(
        std::make_unique<TaskWaitNtp>(timedateConnection, ntpActiveSettled),
        additionalErrorHandler);
}

TaskWaitNtp::TaskWaitNtp(AbstractTimedate1ConnectionPtr timedateConnection, bool ntpActiveSettled) :
    m_timedateConnection(timedateConnection),
    m_ntpActiveSettled(ntpActiveSettled)
{
}

void TaskWaitNtp::start()
{
    if(m_timedateConnection->getNtpActive() == m_ntpActiveSettled) {
        finishTaskQueued(true);
        return;
    }
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigNtpActiveChanged,
            this, [this]() {
        if(m_timedateConnection->getNtpActive() == m_ntpActiveSettled)
            finishTask(true);
    });
}
