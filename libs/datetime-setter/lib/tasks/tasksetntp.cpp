#include "tasksetntp.h"

TaskTemplatePtr TaskSetNtp::create(AbstractTimedate1ConnectionPtr timedateConnection,
                                   bool ntpActive,
                                   std::function<void ()> additionalErrorHandler)
{
    return std::make_unique<TaskSetNtp>(timedateConnection, ntpActive, additionalErrorHandler);
}

TaskSetNtp::TaskSetNtp(AbstractTimedate1ConnectionPtr timedateConnection,
                       bool ntpActive, std::function<void ()> additionalErrorHandler) :
    m_timedateConnection(timedateConnection),
    m_ntpActive(ntpActive),
    m_additionalErrorHandler(additionalErrorHandler)
{
}

void TaskSetNtp::start()
{
    if(m_ntpActive == m_timedateConnection->getNtpActive()) {
        finishTaskQueued(true);
        return;
    }
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigNtpActiveSet, this, [=](bool ok) {
        if(!ok)
            m_additionalErrorHandler();
        finishTask(ok);
    });
    m_timedateConnection->setNtpActive(m_ntpActive);
}
