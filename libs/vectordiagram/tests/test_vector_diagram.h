#ifndef TEST_VECTOR_DIAGRAM_GUI_H
#define TEST_VECTOR_DIAGRAM_GUI_H

#include "vectorpainter.h"
#include <QObject>
#include <QSvgGenerator>
#include <memory>

class test_vector_diagram : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void init();
    void gridOnlySquare();
    void gridOnlyRectangleWide();
    void gridOnlyRectangleNarrow();

    void fullStar_data();
    void fullStar();
private:
    void setSymmetricValues(VectorPainter *painter, double uValue, double iValue, double iAngle);
    double gradToDeg(double angle);
    std::unique_ptr<QSvgGenerator> m_generator;
};

#endif // TEST_VECTOR_DIAGRAM_GUI_H
