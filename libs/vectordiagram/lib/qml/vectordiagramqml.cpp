#include "vectordiagramqml.h"

VectorDiagramQml::VectorDiagramQml(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    setAntialiasing(true);
    setOpaquePainting(true);
}

float VectorDiagramQml::maxVoltage()
{
    return m_vectorPainter.getVectorSettings()->m_lengths.getMaxVoltage();
}

float VectorDiagramQml::maxCurrent()
{
    return m_vectorPainter.getVectorSettings()->m_lengths.getMaxCurrent();
}

void VectorDiagramQml::paint(QPainter *painter)
{
    m_vectorPainter.paint(painter);
    emit maxVoltageChanged();
    emit maxCurrentChanged();
}
