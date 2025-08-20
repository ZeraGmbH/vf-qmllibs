#ifndef TEST_VECTOR_CALC_H
#define TEST_VECTOR_CALC_H

#include <QObject>

class test_vector_calc : public QObject
{
    Q_OBJECT
private slots:
    void deg0();
    void deg359_999();
    void deg360();
    void deg360_111();
    void deg719();
    void deg720();
    void deg721();

    void deg_1();
    void deg_359();
    void deg_360();
    void deg_361();
    void deg_719();
};

#endif // TEST_VECTOR_CALC_H
