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

    void starVectorsNoOvershoot();
    void starVectorsIgnoreLessThanMin();

private:
    void setSymmetricValues(VectorPaintController *painter, double uValue, double iValue, double iAngle);
    double gradToDeg(double angle);
    std::unique_ptr<QSvgGenerator> m_generator;
};

#endif // TEST_VECTOR_DIAGRAM_GUI_H
