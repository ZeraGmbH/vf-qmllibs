#ifndef TEST_VECTOR_NOMINAL_MAXIMUM_H
#define TEST_VECTOR_NOMINAL_MAXIMUM_H

#include <QObject>

class test_vector_nominal_maximum : public QObject
{
    Q_OBJECT
private slots:
    void setNominalMode();
    void setMaximumMode();
    void setMaximumTwice();
};

#endif // TEST_VECTOR_NOMINAL_MAXIMUM_H
