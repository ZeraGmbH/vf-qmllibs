#include "phasordiagram.h"

PhasorDiagram::PhasorDiagram(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    m_gridVisible(true),
    m_gridColor(Qt::darkGray),
    m_circleVisible(true),
    m_circleColor(Qt::darkGray)
{
    setAntialiasing(true);
    setOpaquePainting(true);
}

void PhasorDiagram::setVectorType(const VectorType &VectorType)
{
    VectorPainter::VectorType painterVectorType = VectorPainter::VectorType(VectorType);
    m_vectorPainter.setVectorType(painterVectorType);
    if (m_vectorType != VectorType) {
        m_vectorType = VectorType;
        emit vectorTypeChanged();
        update();
    }
}

const PhasorDiagram::VectorType &PhasorDiagram::vectorType()
{
    return m_vectorType;
}

void PhasorDiagram::paint(QPainter *painter)
{
    m_vectorPainter.paint(painter);
}
