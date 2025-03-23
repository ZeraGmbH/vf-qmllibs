#include "tasksetntp.h"

TaskSetNtp::TaskSetNtp(AbstractTimedate1ConnectionPtr timedateConnection,
                       bool ntpActive) :
    m_timedateConnection(timedateConnection),
    m_ntpActive(ntpActive)
{
}

void TaskSetNtp::start()
{
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigNtpActiveSet, this, [=](bool ok) {
        finishTask(ok);
    });
    m_timedateConnection->setNtpActive(m_ntpActive);
}
