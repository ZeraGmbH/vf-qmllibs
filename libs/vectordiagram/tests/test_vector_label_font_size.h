#ifndef TEST_VECTOR_LABEL_FONT_SIZE_H
#define TEST_VECTOR_LABEL_FONT_SIZE_H

#include <QObject>

class test_vector_label_font_size : public QObject
{
    Q_OBJECT
private slots:
    void setFontSize();
    void setFontTooHigh();
    void setFontTooLow();
};

#endif // TEST_VECTOR_LABEL_FONT_SIZE_H
