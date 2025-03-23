#ifndef TASKSETNTP_H
#define TASKSETNTP_H

#include "abstracttimedate1connection.h"
#include <tasktemplate.h>

class TaskSetNtp : public TaskTemplate
{
    Q_OBJECT
public:
    explicit TaskSetNtp(AbstractTimedate1ConnectionPtr timedateConnection,
                        bool ntpActive);
    void start() override;

private:
    AbstractTimedate1ConnectionPtr m_timedateConnection;
    bool m_ntpActive;
};

#endif // TASKSETNTP_H
