#ifndef TEST_VECTOR_DIAGRAM_GUI_H
#define TEST_VECTOR_DIAGRAM_GUI_H

#include "vectorpaintcontroller.h"
#include <QObject>
#include <QSvgGenerator>
#include <memory>

class test_vector_diagram : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void init();
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
    void setArrowHeight();
    void setArrowWidthWide();
    void setArrowWidthMix();
    void setArrowWidthNarrow();
    void setArrowWidthTooHigh();
    void setArrowWidthTooLow();
    void setFontSize();

    void setDIN();
    void setIEC();
    void setANSI();

    void setStar();
    void setStarNoValues();
    void setTriangle();
    void setTriangleNoCurrent();
    void set3Wire();

    void setNominalMode();
    void setMaximumMode();
    void setMaximumTwice();

    void setVectorStyleZenux0();
    void setVectorStyleZenux30();
    void setVectorStyleWebSam0();
    void setVectorStyleWebSam30();

    void starVectorsNoOvershoot();
    void starVectorsNoOvershootSmall();
    void starVectorsIgnoreLessThanMin();

    void vectorLabelsTooLong_data();
    void vectorLabelsTooLong();

private:
    void setSymmetricValues(VectorPaintController *painter, double uValue, double iValue, double iAngle);
    void setNominalUI(VectorPaintController &vectorPainter, float nominal);
    std::unique_ptr<QSvgGenerator> m_generator;
};

#endif // TEST_VECTOR_DIAGRAM_GUI_H
