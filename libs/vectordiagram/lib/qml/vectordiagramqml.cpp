#include "vectordiagramqml.h"
#include "fuzzypaintdevice.h"
#include <timerfactoryqt.h>
#include <QPicture>

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
    qWarning("updateTimer");

    FuzzyPaintDevice fuzzyPaintDev;
    QPainter testPainter;
    testPainter.begin(&fuzzyPaintDev);
    m_vectorPainter.paint(&testPainter);
    testPainter.end();

    QByteArray paintedRecording = fuzzyPaintDev.getDataRecorded();
    if (m_paintedRecording != paintedRecording) {
        m_paintedRecording = paintedRecording;
        qWarning("update / len %i", paintedRecording.size());
        update();
    }
}

void VectorDiagramQml::paint(QPainter *painter)
{
    qWarning("paint");
    QPicture picture;
    picture.setData(m_paintedRecording.constData(), m_paintedRecording.size());
    m_vectorPainter.paint(painter);
    emit maxVoltageChanged();
    emit maxCurrentChanged();
}

void VectorDiagramQml::startUpdate()
{
    qWarning("start update");
    m_updateTimer = TimerFactoryQt::createSingleShot(10);
    connect(m_updateTimer.get(), &TimerTemplateQt::sigExpired,
            this, &VectorDiagramQml::onUpdateTimer);
    m_updateTimer->start();
}
