#ifndef TEST_TIME_DATE_FACADE_H
#define TEST_TIME_DATE_FACADE_H

#include "abstracttimedate1connection.h"
#include <QObject>

class test_time_date_facade : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void daysInMonth();
    void ntpChange();
private:
    AbstractTimedate1ConnectionPtr m_timeDateConnection;
};

#endif // TEST_TIME_DATE_FACADE_H
