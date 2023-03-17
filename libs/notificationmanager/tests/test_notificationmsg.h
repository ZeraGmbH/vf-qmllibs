#ifndef TEST_NOTIFICATIONMESSAGE_H
#define TEST_NOTIFICATIONMESSAGE_H

#include <QObject>

class test_notificationmsg : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void readMsg();
    void fadeOutCount();
    void fadeOutTime();
};

#endif // TEST_NOTIFICATIONMESSAGE_H
