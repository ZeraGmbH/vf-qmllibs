#include "test_deduce_subnetmask_ipv4.h"
#include "connectiontreeinterface.h"
#include <QTest>

QTEST_MAIN(test_deduce_subnetmask_ipv4)

void test_deduce_subnetmask_ipv4::returnEmptyOnInvalidIp()
{
    ConnectionTreeInterface connectionTree;
    // Just basic checks: Full IP address validation is not our job
    QCOMPARE(connectionTree.deduceSubNetMaskIpv4("foo"), "");
    QCOMPARE(connectionTree.deduceSubNetMaskIpv4("192.168,6.7"), "");
    QCOMPARE(connectionTree.deduceSubNetMaskIpv4("192.168.6.7.8"), "");
}

void test_deduce_subnetmask_ipv4::deduceClassA()
{
    ConnectionTreeInterface connectionTree;
    QCOMPARE(connectionTree.deduceSubNetMaskIpv4("9.15.1.1"), "");
    QCOMPARE(connectionTree.deduceSubNetMaskIpv4("10.15.1.1"), "255.0.0.0");
    QCOMPARE(connectionTree.deduceSubNetMaskIpv4("11.15.1.1"), "");
}

void test_deduce_subnetmask_ipv4::deduceClassB()
{
    ConnectionTreeInterface connectionTree;
    QCOMPARE(connectionTree.deduceSubNetMaskIpv4("172.15.1.1"), "");
    QCOMPARE(connectionTree.deduceSubNetMaskIpv4("172.16.1.1"), "255.255.0.0");
    QCOMPARE(connectionTree.deduceSubNetMaskIpv4("172.31.1.1"), "255.255.0.0");
    QCOMPARE(connectionTree.deduceSubNetMaskIpv4("172.32.1.1"), "");
}

void test_deduce_subnetmask_ipv4::deduceClassC()
{
    ConnectionTreeInterface connectionTree;
    QCOMPARE(connectionTree.deduceSubNetMaskIpv4("192.168.32.1"), "255.255.255.0");
    QCOMPARE(connectionTree.deduceSubNetMaskIpv4("192.169.32.1"), "");
}
