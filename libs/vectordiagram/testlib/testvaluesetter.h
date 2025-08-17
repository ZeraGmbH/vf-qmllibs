#ifndef TESTVALUESETTER_H
#define TESTVALUESETTER_H

#include "vectorpaintcontroller.h"

class TestValueSetter
{
public:
    static void setSymmetricValues(VectorPaintController *painter, double uValue, double iValue, double iAngle);
    static void setNominalUI(VectorPaintController &vectorPainter, float nominal);
};

#endif // TESTVALUESETTER_H
