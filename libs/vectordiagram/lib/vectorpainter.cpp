#include "vectorpainter.h"
#include <QFont>
#include <QGradient>
#include <QPainterPath>
#include <QMultiMap>
#include <math.h>

void VectorPainter::setMaxOvershootFactor(float maxOvershoot)
{
    m_maxOvershoot = maxOvershoot;
}

void VectorPainter::setNominalVoltage(float nomVoltage)
{
    m_nomVoltage = nomVoltage;
}

void VectorPainter::setMinVoltage(float minVoltage)
{
    m_minVoltage = minVoltage;
}

void VectorPainter::setNominalCurrent(float nomCurrent)
{
    m_nomCurrent = nomCurrent;
}

void VectorPainter::setMinCurrent(float minCurrent)
{
    m_minCurrent = minCurrent;
}

void VectorPainter::setVectorType(VectorType vectorType)
{
    m_vectorType = vectorType;
}

void VectorPainter::setGridVisible(bool gridVisible)
{
    m_gridVisible = gridVisible;
}

void VectorPainter::setGridColor(const QColor &gridColor)
{
    m_gridColor = gridColor;
}

void VectorPainter::setCircleVisible(bool circleVisible)
{
    m_circleVisible = circleVisible;
}

void VectorPainter::setCircleColor(const QColor &circleColor)
{
    m_circleColor = circleColor;
}

void VectorPainter::setVector(int idx, const QVector2D &vector)
{
    m_vector[idx] = vector;
}

void VectorPainter::setVectorColor(int idx, const QColor &vectorColor)
{
    m_vectorColor[idx] = vectorColor;
}

void VectorPainter::setVectorLabel(int idx, const QString &vectorLabel)
{
    m_vectorLabel[idx] = vectorLabel;
}

void VectorPainter::setFontForLabels(QPainter *painter)
{
    const int minXy = std::min(height(painter), width(painter));
    QFont defaultFont;
    defaultFont.setPixelSize(minXy > 0.0 ? minXy / 25 : 10.0);
    defaultFont.setFamily("Sans");
    painter->setFont(defaultFont);
}

void VectorPainter::paint(QPainter *painter)
{
    m_fromX = painter->device()->width() / 2;
    m_fromY = painter->device()->height() / 2;

    setFontForLabels(painter);
    drawGrid(painter);
    drawCircle(painter);
}

void VectorPainter::drawGrid(QPainter *painter)
{
    if(!m_gridVisible)
        return;

    painter->setPen(QPen(m_gridColor, getGridAndCircleLineWidth(painter)));
    float lenFromCenter = getClipSquareLen(painter) / 2;
    painter->drawLine(m_fromX-lenFromCenter, m_fromY, m_fromX+lenFromCenter, m_fromY); // x axis
    painter->drawLine(m_fromX, m_fromY-lenFromCenter, m_fromX, m_fromY+lenFromCenter); // y axis
}

// Some thoughts:
// overshoot = 1.0
// |        /        |
// | label |<--------|
// |        \        |

// overshoot = maxOvershoot
// |           /     |
// | label <--|------|
// |           \     |

// circle radius is nominal

constexpr float totalLenAvail = 1.0;
constexpr float extraLabelLenFromAvail = 0.2;
constexpr float vectorLenFromAvail = totalLenAvail - extraLabelLenFromAvail;

float VectorPainter::getVectorLenMaxInPixels(const QPainter *painter)
{
    const float pixelsAvailforVector = getClipSquareLen(painter) / 2 * vectorLenFromAvail;
    return pixelsAvailforVector;
}

float VectorPainter::getVectorLenNominalInPixels(const QPainter *painter)
{
    return getVectorLenMaxInPixels(painter) / m_maxOvershoot;
}


void VectorPainter::drawCircle(QPainter *painter)
{
    if(!m_circleVisible)
        return;

    painter->setPen(QPen(m_circleColor, getGridAndCircleLineWidth(painter)));
    const float radius = getVectorLenNominalInPixels(painter);
    painter->drawArc(
        m_fromX - radius,
        m_fromY - radius,
        2 * radius,
        2 * radius,
        0, 5760);
}

float VectorPainter::getClipSquareLen(const QPainter *painter)
{
    const float w = width(painter);
    const float h = height(painter);
    return std::min(h, w);
}

float VectorPainter::getGridAndCircleLineWidth(const QPainter *painter)
{
    return getClipSquareLen(painter) * 0.005; // to be adjusted...
}


int VectorPainter::height(const QPainter *painter)
{
    QPaintDevice *paintDevice = painter->device();
    if (paintDevice)
        return paintDevice->height();
    return 1;
}

int VectorPainter::width(const QPainter *painter)
{
    QPaintDevice *paintDevice = painter->device();
    if (paintDevice)
        return paintDevice->width();
    return 1;
}

