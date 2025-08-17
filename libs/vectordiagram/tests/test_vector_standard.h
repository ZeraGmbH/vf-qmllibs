#ifndef TEST_VECTOR_STANDARD_H
#define TEST_VECTOR_STANDARD_H

#include <QObject>

class test_vector_standard : public QObject
{
    Q_OBJECT
private slots:
    void setDIN();
    void setDINUAngle();
    void setIEC();
    void setANSI();
    void setANSIUAngle();
};

#endif // TEST_VECTOR_STANDARD_H
