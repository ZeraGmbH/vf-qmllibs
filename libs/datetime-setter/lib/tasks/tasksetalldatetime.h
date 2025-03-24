#ifndef TASKSETALLDATETIME_H
#define TASKSETALLDATETIME_H

#include "abstracttimedate1connection.h"
#include <tasktemplate.h>
#include <taskcontainerinterface.h>

class TaskSetAllDateTime : public TaskTemplate
{
    Q_OBJECT
public:
    static TaskTemplatePtr create(AbstractTimedate1ConnectionPtr timedateConnection,
                                  const QString &timezone, bool ntpActive, QDateTime datetime,
                                  std::shared_ptr<QStringList> errorMessages);
    explicit TaskSetAllDateTime(AbstractTimedate1ConnectionPtr timedateConnection,
                             const QString &timezone, bool ntpActive, QDateTime datetime,
                             std::shared_ptr<QStringList> errorMessages);
    void start() override;

private:
    TaskTemplatePtr getTimezoneTask(AbstractTimedate1ConnectionPtr timedateConnection,
                                   const QString &timezone);
    TaskTemplatePtr getNtpTask(AbstractTimedate1ConnectionPtr timedateConnection,
                               bool ntpActive);
    TaskTemplatePtr getDatetimeTask(AbstractTimedate1ConnectionPtr timedateConnection,
                                    QDateTime datetime);

    TaskContainerInterfacePtr m_tasks;
    std::shared_ptr<QStringList> m_errorMessages;
};

#endif // TASKSETALLDATETIME_H
