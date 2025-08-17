#ifndef TEST_VECTOR_ARROW_HEAD_H
#define TEST_VECTOR_ARROW_HEAD_H

#include <QObject>

class test_vector_arrow_head : public QObject
{
    Q_OBJECT
private slots:
    void setArrowHeight();
    void setArrowWidthWide();
    void setArrowWidthMix();
    void setArrowWidthNarrow();
    void setArrowWidthTooHigh();
    void setArrowWidthTooLow();
};

#endif // TEST_VECTOR_ARROW_HEAD_H
