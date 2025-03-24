#include "tasksetalldatetime.h"
#include "tasksettimezone.h"
#include "tasksetntp.h"
#include "taskwaitntp.h"
#include "tasksetdatetime.h"
#include <taskcontainersequence.h>
#include <taskdecoratortimeout.h>
#include <zeratranslation.h>

TaskTemplatePtr TaskSetAllDateTime::create(AbstractTimedate1ConnectionPtr timedateConnection,
                                        const QString &timezone, bool ntpActive, QDateTime datetime,
                                        std::shared_ptr<QStringList> errorMessages)
{
    return std::make_unique<TaskSetAllDateTime>(timedateConnection,
                                             timezone, ntpActive, datetime,
                                             errorMessages);
}

TaskSetAllDateTime::TaskSetAllDateTime(AbstractTimedate1ConnectionPtr timedateConnection,
                                 const QString &timezone, bool ntpActive, QDateTime datetime,
                                 std::shared_ptr<QStringList> errorMessages) :
    m_tasks(TaskContainerSequence::create()),
    m_errorMessages(errorMessages)
{
    m_tasks->addSub(getTimezoneTask(timedateConnection, timezone));
    m_tasks->addSub(getNtpTask(timedateConnection, ntpActive));
    if(!ntpActive)
        m_tasks->addSub(getDatetimeTask(timedateConnection, datetime));
}

void TaskSetAllDateTime::start()
{
    connect(m_tasks.get(), &TaskTemplate::sigFinish,
            this, &TaskTemplate::sigFinish);
    m_tasks->start();
}

TaskTemplatePtr TaskSetAllDateTime::getTimezoneTask(AbstractTimedate1ConnectionPtr timedateConnection,
                                                    const QString &timezone)
{
    const QString errMsgTimezone = ZeraTranslation::getInstance()->trValue("Set timezone failed!").toString();
    return TaskSetTimezone::create(timedateConnection,
                                   timezone,
                                   [this, errMsgTimezone]() {
                                       m_errorMessages->append(errMsgTimezone);
                                   });
}

TaskTemplatePtr TaskSetAllDateTime::getNtpTask(AbstractTimedate1ConnectionPtr timedateConnection,
                                               bool ntpActive)
{
    const QString errMsgNtp = ntpActive ?
                                  ZeraTranslation::getInstance()->trValue("NTP activate failed!").toString() :
                                  ZeraTranslation::getInstance()->trValue("NTP deactivate failed!").toString();
    TaskContainerInterfacePtr task = TaskContainerSequence::create();
    std::function<void ()> errorHandler = [this, errMsgNtp]() {
        m_errorMessages->append(errMsgNtp);
    };
    // No timeout for DBUS response TaskSetNtp: on dev machine we have to enter password
    task->addSub(TaskSetNtp::create(timedateConnection,
                                    ntpActive,
                                    errorHandler));
    task->addSub(TaskDecoratorTimeout::wrapTimeout(ntpSettleTimeoutMs,
                                                   TaskWaitNtp::create(timedateConnection, ntpActive),
                                                   errorHandler));
    return task;
}

TaskTemplatePtr TaskSetAllDateTime::getDatetimeTask(AbstractTimedate1ConnectionPtr timedateConnection,
                                                    QDateTime datetime)
{
    const QString errMsgDateTime = ZeraTranslation::getInstance()->trValue("Set date/time failed!").toString();
    return TaskSetDateTime::create(timedateConnection,
                                            datetime,
                                            [this, errMsgDateTime]() {
                                                m_errorMessages->append(errMsgDateTime);
                                            });
}
