#ifndef TEST_VECTOR_LINE_WIDTH_H
#define TEST_VECTOR_LINE_WIDTH_H

#include <QObject>

class test_vector_line_width : public QObject
{
    Q_OBJECT
private slots:
    void setVectorLineWidth();
    void setVectorLineWidthTooHigh();
    void setVectorLineWidthTooLow();
};

#endif // TEST_VECTOR_LINE_WIDTH_H
