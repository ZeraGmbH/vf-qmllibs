#ifndef TEST_TIMEDATE1_MOCK_H
#define TEST_TIMEDATE1_MOCK_H

#include <QObject>

class test_timedate1_mock : public QObject
{
    Q_OBJECT
private slots:
    void availableTimezones();
};

#endif // TEST_TIMEDATE1_MOCK_H
