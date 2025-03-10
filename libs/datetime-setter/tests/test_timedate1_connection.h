#ifndef TEST_TIMEDATE1_CONNECTION_H
#define TEST_TIMEDATE1_CONNECTION_H

#include "abstracttimedate1connection.h"
#include <memory>

class test_timedate1_connection : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase_data();
    void init();
    void cleanup();

    void availableTimezones();
    void disableNtp();
    void disableEnableNtp();
    void changeTimezoneValid();
    void changeTimezoneInvalid();
    void changeTimeNtpOn();
    void changeTimeNtpOff();
private:
    void setupConnection();
    void waitNtpSync();
    std::unique_ptr<AbstractTimedate1Connection> m_connection;
    QString m_hostTimezone;
    int m_ntpSyncMaxWaitMs = 0;
    int m_waitTimeToEnterPolkitPassword = 0;
    int m_waitTimeNoPolkit = 0;
};

#endif // TEST_TIMEDATE1_CONNECTION_H
