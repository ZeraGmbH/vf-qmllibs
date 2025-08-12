#ifndef TESTPRIMITIVEPAINTERLABEL_H
#define TESTPRIMITIVEPAINTERLABEL_H

#include <abstractvectorpainter.h>
#include "vectorsettingsgeometry.h"

class TestPrimitivePainterLabel : public AbstractVectorPainter
{
public:
    TestPrimitivePainterLabel();
    void paint(QPainter *painter) override;

    VectorSettingsGeometry m_settingsGeometry;
};

#endif // TESTPRIMITIVEPAINTERLABEL_H
