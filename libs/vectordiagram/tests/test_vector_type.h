#ifndef TEST_VECTOR_TYPE_H
#define TEST_VECTOR_TYPE_H

#include <QObject>

class test_vector_type : public QObject
{
    Q_OBJECT
private slots:
    void setStar();
    void setStarNoValues();
    void setTriangle();
    void setTriangleNoCurrent();
    void set3Wire();
};

#endif // TEST_VECTOR_TYPE_H
