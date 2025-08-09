#ifndef TESTPRIMITIVEVECTORPAINTER_H
#define TESTPRIMITIVEVECTORPAINTER_H

#include "vectorsettingsgeometry.h"
#include <abstractvectorpainter.h>

class TestPrimitiveVectorPainter : public AbstractVectorPainter
{
public:
    TestPrimitiveVectorPainter();
    void paint(QPainter *painter) override;

    VectorSettingsGeometry m_settingsGeometry;

private:
    void draw2Vectors(QPainter *painter);
};

#endif // TESTPRIMITIVEVECTORPAINTER_H
