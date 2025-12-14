#include "vectordiagramqml.h"
#include <timerfactoryqt.h>

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

void VectorDiagramQml::onUpdateTimer()
{
    update();
}

void VectorDiagramQml::paint(QPainter *painter)
{
    m_vectorPainter.paint(painter);
    emit maxVoltageChanged();
    emit maxCurrentChanged();
}

void VectorDiagramQml::startUpdate()
{
    m_updateTimer = TimerFactoryQt::createSingleShot(20);
    connect(m_updateTimer.get(), &TimerTemplateQt::sigExpired,
            this, &VectorDiagramQml::onUpdateTimer);
    m_updateTimer->start();
}
