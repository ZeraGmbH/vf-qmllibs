#include "phasordiagram.h"

PhasorDiagram::PhasorDiagram(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    m_gridColor(Qt::darkGray)
{
    setAntialiasing(true);
    setOpaquePainting(true);
}

void PhasorDiagram::setVectorView(const VectorView &vectorView)
{
    VectorPainter::VectorView painterVectorView = VectorPainter::VectorView(vectorView);
    m_vectorPainter.setVectorView(painterVectorView);
    if (m_vectorView != vectorView) {
        m_vectorView = vectorView;
        emit vectorViewChanged();
        update();
    }
}

const PhasorDiagram::VectorView &PhasorDiagram::vectorView()
{
    return m_vectorView;
}

void PhasorDiagram::paint(QPainter *painter)
{
    m_vectorPainter.paint(painter);
}
