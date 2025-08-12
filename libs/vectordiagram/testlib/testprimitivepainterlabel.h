#ifndef TESTPRIMITIVEPAINTERLABEL_H
#define TESTPRIMITIVEPAINTERLABEL_H

#include <abstractvectorpainter.h>
#include "vectorsettings.h"

class TestPrimitivePainterLabel : public AbstractVectorPainter
{
public:
    TestPrimitivePainterLabel();
    void paint(QPainter *painter) override;

    VectorSettings m_vectorSettings;
};

#endif // TESTPRIMITIVEPAINTERLABEL_H
