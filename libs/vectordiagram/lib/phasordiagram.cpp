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

void PhasorDiagram::setVectorType(const VectorType &vectorType)
{
    VectorPainter::VectorType painterVectorType = VectorPainter::VectorType(vectorType);
    m_vectorPainter.setVectorType(painterVectorType);
    if (m_vectorType != vectorType) {
        m_vectorType = vectorType;
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
