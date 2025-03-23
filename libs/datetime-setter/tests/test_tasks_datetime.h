#ifndef TEST_TASKS_DATETIME_H
#define TEST_TASKS_DATETIME_H

#include "testtimedate1connection.h"
#include <QDateTime>

class test_tasks_datetime : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void setDateTimeNotSucessful();
    void setDateTimeSucessful();

    void setNtpOffOn();
    void setNtpNotAvail();

    void setTimezoneNotSuccesful();
    void setTimezoneSuccesful();
private:
    std::shared_ptr<TestTimedate1Connection> m_timeDateConnection;
    QDateTime m_testDatetime;
};

#endif // TEST_TASKS_DATETIME_H
