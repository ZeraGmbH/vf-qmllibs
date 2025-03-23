#ifndef TASKSETDATETIME_H
#define TASKSETDATETIME_H

#include "abstracttimedate1connection.h"
#include <tasktemplate.h>
#include <QDateTime>
#include <QTime>

class TaskSetDateTime : public TaskTemplate
{
    Q_OBJECT
public:
    explicit TaskSetDateTime(AbstractTimedate1ConnectionPtr timedateConnection,
                             QDateTime datetime);
    void start() override;

private:
    AbstractTimedate1ConnectionPtr m_timedateConnection;
    QDateTime m_datetime;
};

#endif // TASKSETDATETIME_H
