#ifndef TESTVALUESETTER_H
#define TESTVALUESETTER_H

#include "vectorpaintcontroller.h"
#include <complex>

class TestValueSetter
{
public:
    static void setSymmetricValues(VectorPaintController *painter, double uValue, double iValue, double iAngle);
    static void setVectors(VectorPaintController *painter, QVector<std::complex<float> > vectors);
    static void setNominalUI(VectorPaintController &vectorPainter, float nominal);
private:
    const static QVector<QString> m_testLabels;
    const static QVector<QColor> m_testColors;
};

#endif // TESTVALUESETTER_H
