#include "vectordiagramqml.h"

VectorDiagramQml::VectorDiagramQml(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    setAntialiasing(true);
    setOpaquePainting(true);
}

void VectorDiagramQml::paint(QPainter *painter)
{
    m_vectorPainter.paint(painter);
}
