#include "phasordiagram.h"

PhasorDiagram::PhasorDiagram(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    setAntialiasing(true);
    setOpaquePainting(true);
}

void PhasorDiagram::paint(QPainter *painter)
{
    m_vectorPainter.paint(painter);
}
