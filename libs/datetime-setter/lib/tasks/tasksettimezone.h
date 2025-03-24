#ifndef TASKSETTIMEZONE_H
#define TASKSETTIMEZONE_H

#include "abstracttimedate1connection.h"
#include <tasktemplate.h>

class TaskSetTimezone : public TaskTemplate
{
    Q_OBJECT
    static constexpr int defaultTimeout = 3000;
public:
    static TaskTemplatePtr create(AbstractTimedate1ConnectionPtr timedateConnection,
                                  const QString &timezone,
                                  std::function<void()> additionalErrorHandler = []{}, int timeoutMs = defaultTimeout);
    explicit TaskSetTimezone(AbstractTimedate1ConnectionPtr timedateConnection,
                             const QString &timezone);
    void start() override;

private:
    AbstractTimedate1ConnectionPtr m_timedateConnection;
    QString m_timezone;
};

#endif // TASKSETTIMEZONE_H
