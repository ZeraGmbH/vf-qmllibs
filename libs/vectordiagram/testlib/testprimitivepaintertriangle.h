#ifndef TESTPRIMITIVEPAINTERTRIANGLE_H
#define TESTPRIMITIVEPAINTERTRIANGLE_H

#include "vectorsettings.h"
#include <abstractvectorpainter.h>

class TestPrimitivePainterTriangle : public AbstractVectorPainter
{
public:
    TestPrimitivePainterTriangle();
    void paint(QPainter *painter) override;

    VectorSettings m_vectorSettings;

private:
    void drawTriangle(QPainter *painter);
};

#endif // TESTPRIMITIVEPAINTERTRIANGLE_H
