#ifndef TEST_NOTIFICATIONMESSAGE_H
#define TEST_NOTIFICATIONMESSAGE_H

#include <QObject>

class test_notificationmessage : public QObject
{
    Q_OBJECT
private slots:
    void readMsg();
};

#endif // TEST_NOTIFICATIONMESSAGE_H
