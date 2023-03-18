#include "test_notificationmsgcontainer.h"
#include "notificationmsgcontainer.h"
#include "notificationmsgexpiring.h"
#include <timerfactoryqtfortest.h>
#include <timemachinefortest.h>
#include <QSignalSpy>
#include <QTest>

QTEST_MAIN(test_notificationmsgcontainer)

void test_notificationmsgcontainer::init()
{
    TimerFactoryQtForTest::enableTest();
}

void test_notificationmsgcontainer::addAndGetMsgs()
{
    NotificationMsgContainer container;
    container.addMsg(std::make_shared<NotificationMsg>("bar"));
    container.addMsg(std::make_shared<NotificationMsg>("foo"));
    container.addMsg(std::make_shared<NotificationMsg>("baz"));
    QVector<NotificationMsgPtr> msgs = container.getMsgs();
    QCOMPARE(msgs.size(), 3);
    QCOMPARE(msgs[0]->getMsg(), "bar");
    QCOMPARE(msgs[1]->getMsg(), "foo");
    QCOMPARE(msgs[2]->getMsg(), "baz");
}

void test_notificationmsgcontainer::addAndClearMsgs()
{
    NotificationMsgContainer container;
    container.addMsg(std::make_shared<NotificationMsg>("bar"));
    container.addMsg(std::make_shared<NotificationMsg>("foo"));
    QVector<NotificationMsgPtr> msgs = container.getMsgs();
    QCOMPARE(msgs.size(), 2);
    container.clear();
    msgs = container.getMsgs();
    QCOMPARE(msgs.size(), 0);
}

void test_notificationmsgcontainer::addOneAndWaitForFade()
{
    NotificationMsgContainer container;
    QSignalSpy spy(&container, &NotificationMsgContainer::sigMsgFaded);
    container.addMsg(std::make_shared<NotificationMsgExpiring>("bar", 100));
    TimeMachineForTest::getInstance()->processTimers(50);
    QVector<NotificationMsgPtr> msgs = container.getMsgs();
    QCOMPARE(spy.count(), 0);
    QCOMPARE(msgs.size(), 1);
    TimeMachineForTest::getInstance()->processTimers(50);
    msgs = container.getMsgs();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(msgs.size(), 0);
}

void test_notificationmsgcontainer::addThreeSecondFade()
{
    NotificationMsgContainer container;
    container.addMsg(std::make_shared<NotificationMsg>("bar"));
    container.addMsg(std::make_shared<NotificationMsgExpiring>("foo", 150));
    container.addMsg(std::make_shared<NotificationMsg>("baz"));
    TimeMachineForTest::getInstance()->processTimers(150);
    QVector<NotificationMsgPtr> msgs = container.getMsgs();
    QCOMPARE(msgs.size(), 2);
    QCOMPARE(msgs[0]->getMsg(), "bar");
    QCOMPARE(msgs[1]->getMsg(), "baz");
}

