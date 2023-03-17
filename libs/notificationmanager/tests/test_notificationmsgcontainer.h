#ifndef TEST_NOTIFICATIONMSGCONTAINER_H
#define TEST_NOTIFICATIONMSGCONTAINER_H

#include <QObject>

class test_notificationmsgcontainer : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void addAndGetMsgs();
    void addAndClearMsgs();
    void addOneAndWaitForFade();
    void addThreeSecondFade();
};

#endif // TEST_NOTIFICATIONMSGCONTAINER_H
