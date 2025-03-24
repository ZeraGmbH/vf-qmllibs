#include "tasksetdatetime.h"
#include <QDateTime>

TaskTemplatePtr TaskSetDateTime::create(AbstractTimedate1ConnectionPtr timedateConnection,
                                        QDateTime datetime,
                                        std::function<void ()> additionalErrorHandler)
{
    return std::make_unique<TaskSetDateTime>(timedateConnection, datetime, additionalErrorHandler);
}

TaskSetDateTime::TaskSetDateTime(AbstractTimedate1ConnectionPtr timedateConnection,
                                 QDateTime datetime, std::function<void ()> additionalErrorHandler) :
    m_timedateConnection(timedateConnection),
    m_datetime(datetime),
    m_additionalErrorHandler(additionalErrorHandler)
{
}

void TaskSetDateTime::start()
{
    connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigDateTimeSet, this, [=](bool ok) {
        if(!ok)
            m_additionalErrorHandler();
        finishTask(ok);
    });
    m_timedateConnection->setDateTime(m_datetime);
}
