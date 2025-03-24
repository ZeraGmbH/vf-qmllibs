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
    QStringList getErrorMessages() const;
private:
    TaskContainerInterfacePtr m_tasks;
    std::shared_ptr<QStringList> m_errorMessages;
};

#endif // TASKSETALLDATETIME_H
