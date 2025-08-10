#ifndef TESTPRIMITIVEPAINTERSTAR_H
#define TESTPRIMITIVEPAINTERSTAR_H

#include "vectorsettingsgeometry.h"
#include <abstractvectorpainter.h>

class TestPrimitivePainterStar : public AbstractVectorPainter
{
public:
    TestPrimitivePainterStar();
    void paint(QPainter *painter) override;

    VectorSettingsGeometry m_settingsGeometry;

private:
    void draw2Vectors(QPainter *painter);
};

#endif // TESTPRIMITIVEPAINTERSTAR_H
