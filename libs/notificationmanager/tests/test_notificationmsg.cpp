#include "test_notificationmsg.h"
#include "notificationmsg.h"
#include "notificationmsgexpiring.h"
#include <timerfactoryqtfortest.h>
#include <timemachinefortest.h>
#include <QSignalSpy>
#include <QTest>

QTEST_MAIN(test_notificationmsg)

void test_notificationmsg::init()
{
    TimerFactoryQtForTest::enableTest();
}

void test_notificationmsg::readMsg()
{
    NotificationMsg msg1("foo");
    NotificationMsg msg2("bar");
    QCOMPARE(msg1.getMsg(), "foo");
    QCOMPARE(msg2.getMsg(), "bar");
}

void test_notificationmsg::fadeOutCount()
{
    NotificationMsgExpiring msg("foo", 100);
    QSignalSpy spy(&msg, &NotificationMsg::sigFadeOut);
    TimeMachineForTest::getInstance()->processTimers(1500);
    QCOMPARE(spy.count(), 1);
}

void test_notificationmsg::fadeOutTime()
{
    NotificationMsgExpiring msg("foo", 100);
    QSignalSpy spy(&msg, &NotificationMsg::sigFadeOut);
    TimeMachineForTest::getInstance()->processTimers(99);
    QCOMPARE(spy.count(), 0);
    TimeMachineForTest::getInstance()->processTimers(1);
    QCOMPARE(spy.count(), 1);
}
