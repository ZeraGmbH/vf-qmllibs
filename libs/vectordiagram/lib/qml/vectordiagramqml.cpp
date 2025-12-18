#include "vectordiagramqml.h"
#include "fuzzypaintdevice.h"
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
    FuzzyPaintDevice fuzzyPaintDev;
    QPainter testPainter;
    testPainter.begin(&fuzzyPaintDev);
    m_vectorPainter.paint(&testPainter);
    testPainter.end();

    quint32 newCrc = fuzzyPaintDev.getCrc32();
    if (m_lastPaintCrc != newCrc) {
        m_lastPaintCrc = newCrc;
        update();
    }
}

void VectorDiagramQml::paint(QPainter *painter)
{
    m_vectorPainter.paint(painter);
    emit maxVoltageChanged();
    emit maxCurrentChanged();
}

void VectorDiagramQml::startUpdate()
{
    m_updateTimer = TimerFactoryQt::createSingleShot(10);
    connect(m_updateTimer.get(), &TimerTemplateQt::sigExpired,
            this, &VectorDiagramQml::onUpdateTimer);
    m_updateTimer->start();
}
