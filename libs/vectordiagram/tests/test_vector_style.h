#ifndef TEST_VECTOR_STYLE_H
#define TEST_VECTOR_STYLE_H

#include <QObject>

class test_vector_style : public QObject
{
    Q_OBJECT
private slots:
    void setVectorStyleZenux0();
    void setVectorStyleZenux30();
    void setVectorStyleWebSam0();
    void setVectorStyleWebSam30();

};

#endif // TEST_VECTOR_STYLE_H
