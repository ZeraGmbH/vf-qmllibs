#include "fuzzypaintdevice.h"
#include <QGuiApplication>
#include <QScreen>

FuzzyPaintDevice::FuzzyPaintDevice() :
    m_fuzzyEngine(std::make_unique<FuzzyPaintEngine>()),
    m_boundingRect(QRect(0, 0, 100, 100)) // This is bound to PRECISION_TYPE in fuzzypaintengine.cpp
{
}

QByteArray FuzzyPaintDevice::getDataRecorded() const
{
    return m_fuzzyEngine->getDataRecorded();
}

QPaintEngine *FuzzyPaintDevice::paintEngine() const
{
    return m_fuzzyEngine.get();
}

// simplified qt_defaultDpiX()
static int defaultDpiX()
{
    if (const QScreen *screen = QGuiApplication::primaryScreen())
        return qRound(
            screen->logicalDotsPerInchX());
    return 100;
}

// simplified qt_defaultDpiY()
static int defaultDpiY()
{
    if (const QScreen *screen = QGuiApplication::primaryScreen())
        return qRound(
            screen->logicalDotsPerInchY());
    return 100;
}

int FuzzyPaintDevice::metric(PaintDeviceMetric metric) const
{
    // stolen from QPicture::metric(PaintDeviceMetric m)
    int val;
    QRect brect = m_boundingRect;
    switch (metric) {
    case PdmWidth:
        val = brect.width();
        break;
    case PdmHeight:
        val = brect.height();
        break;
    case PdmWidthMM:
        val = int(25.4/defaultDpiX()*brect.width());
        break;
    case PdmHeightMM:
        val = int(25.4/defaultDpiY()*brect.height());
        break;
    case PdmDpiX:
    case PdmPhysicalDpiX:
        val = defaultDpiX();
        break;
    case PdmDpiY:
    case PdmPhysicalDpiY:
        val = defaultDpiY();
        break;
    case PdmNumColors:
        val = 16777216;
        break;
    case PdmDepth:
        val = 24;
        break;
    case PdmDevicePixelRatio:
        val = 1;
        break;
    case PdmDevicePixelRatioScaled:
        val = 1 * QPaintDevice::devicePixelRatioFScale();
        break;
    default:
        val = 0;
        qWarning(
            "FuzzyPaintDevice::metric: Invalid metric command");
    }
    return val;
}
