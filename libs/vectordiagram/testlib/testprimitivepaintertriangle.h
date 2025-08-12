#ifndef TESTPRIMITIVEPAINTERTRIANGLE_H
#define TESTPRIMITIVEPAINTERTRIANGLE_H

#include "vectorsettingsgeometry.h"
#include <abstractvectorpainter.h>

class TestPrimitivePainterTriangle : public AbstractVectorPainter
{
public:
    TestPrimitivePainterTriangle();
    void paint(QPainter *painter) override;

    VectorSettingsGeometry m_vectorSettings;

private:
    void drawTriangle(QPainter *painter);
};

#endif // TESTPRIMITIVEPAINTERTRIANGLE_H
