#ifndef TASKWAITNTP_H
#define TASKWAITNTP_H

#include "abstracttimedate1connection.h"
#include <tasktemplate.h>

class TaskWaitNtp : public TaskTemplate
{
    Q_OBJECT
public:
    static TaskTemplatePtr create(AbstractTimedate1ConnectionPtr timedateConnection,
                                  bool ntpActiveSettled,
                                  std::function<void()> additionalErrorHandler = []{});
    explicit TaskWaitNtp(AbstractTimedate1ConnectionPtr timedateConnection,
                        bool ntpActiveSettled);
    void start() override;

private:
    AbstractTimedate1ConnectionPtr m_timedateConnection;
    bool m_ntpActiveSettled;
};

#endif // TASKWAITNTP_H
