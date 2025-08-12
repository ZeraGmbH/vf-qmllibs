#ifndef TESTPRIMITIVEPAINTERSTAR_H
#define TESTPRIMITIVEPAINTERSTAR_H

#include "vectorsettings.h"
#include <abstractvectorpainter.h>

class TestPrimitivePainterStar : public AbstractVectorPainter
{
public:
    TestPrimitivePainterStar();
    void paint(QPainter *painter) override;

    VectorSettings m_vectorSettings;

private:
    void draw2Vectors(QPainter *painter);
};

#endif // TESTPRIMITIVEPAINTERSTAR_H
