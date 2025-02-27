#ifndef TEST_TIMEDATE1_CONNECTION_H
#define TEST_TIMEDATE1_CONNECTION_H

#include "timedate1connection.h"

class test_timedate1_connection : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void init();
    void cleanup();

    void availableTimezones();
    void enableDisableNtp();
    void changeTimezone();
private:
    std::unique_ptr<Timedate1Connection> m_connection;
};

#endif // TEST_TIMEDATE1_CONNECTION_H
