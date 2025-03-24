#ifndef TASKSETNTP_H
#define TASKSETNTP_H

#include "abstracttimedate1connection.h"
#include <tasktemplate.h>

class TaskSetNtp : public TaskTemplate
{
    Q_OBJECT
public:
    static TaskTemplatePtr create(AbstractTimedate1ConnectionPtr timedateConnection,
                                  bool ntpActive,
                                  std::function<void()> additionalErrorHandler = []{});
    explicit TaskSetNtp(AbstractTimedate1ConnectionPtr timedateConnection,
                        bool ntpActive,
                        std::function<void()> additionalErrorHandler = []{});
    void start() override;

private:
    AbstractTimedate1ConnectionPtr m_timedateConnection;
    bool m_ntpActive;
    std::function<void()> m_additionalErrorHandler;
};

#endif // TASKSETNTP_H
