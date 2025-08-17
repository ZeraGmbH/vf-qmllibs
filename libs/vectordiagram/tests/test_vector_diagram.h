#ifndef TEST_VECTOR_DIAGRAM_GUI_H
#define TEST_VECTOR_DIAGRAM_GUI_H

#include <QObject>

class test_vector_diagram : public QObject
{
    Q_OBJECT
private slots:
    void noGridSquare();
    void gridOnlySquare();
    void gridOnlyRectangleWide();
    void gridOnlyRectangleNarrow();
    void gridOnlyBlue();

    void gridAndCircleNoOvershoot();
    void gridAndCircleOvershoot();
    void gridAndCircleBlue();
    void setCrossAndCircleLineWidth();
    void setVectorLineWidth();

    void setFontSize();

    void starVectorsNoOvershoot();
    void starVectorsNoOvershootSmall();
    void starVectorsIgnoreLessThanMin();

    void vectorLabelsTooLong_data();
    void vectorLabelsTooLong();

    void vectorLabelsTooShort_data();
    void vectorLabelsTooShort();
};

#endif // TEST_VECTOR_DIAGRAM_GUI_H
