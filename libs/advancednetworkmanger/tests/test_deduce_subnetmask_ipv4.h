#ifndef TEST_DEDUCE_SUBNETMASK_IPV4_H
#define TEST_DEDUCE_SUBNETMASK_IPV4_H

#include <QObject>

class test_deduce_subnetmask_ipv4 : public QObject
{
    Q_OBJECT
private slots:
    void returnEmptyOnInvalidIp();
    void deduceClassA();
    void deduceClassB();
    void deduceClassC();
};

#endif // TEST_DEDUCE_SUBNETMASK_IPV4_H
