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

void VectorPainter::paint(QPainter *painter)
{
    m_fromX = painter->device()->width() / 2;
    m_fromY = painter->device()->height() / 2;

    setFontForLabels(painter);
    drawGrid(painter);
    drawCircle(painter);

    for(int idx=0; idx<COUNT_PHASES*2; ++idx) {
        if (m_vector[idx].length() > getMinimalUOrI(idx)) {
            drawVectorLine(painter, idx);
            drawArrowHead(painter, idx);
        }
    }
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


void VectorPainter::drawCircle(QPainter *painter)
{
    if(!m_circleVisible)
        return;

    float lineWidth = getGridAndCircleLineWidth(painter);
    painter->setPen(QPen(m_circleColor, lineWidth));
    const float radius = getVectorLenNominalInPixels(painter);
    QRect circleRect(
        round(m_fromX - radius),
        round(m_fromY - radius),
        round(2 * radius),
        round(2 * radius));
    painter->drawArc(circleRect, 0, 16*360);
}

void VectorPainter::drawVectorLine(QPainter *painter, int idx)
{
    const float lineWidth = getVectorLineWidth(painter);
    painter->setPen(QPen(m_vectorColor[idx], lineWidth));
    PixelVector pixVector = calcPixVec(painter, idx, getArrowHeight(painter)); // still overlap lineWidth/2
    QLine line(round(m_fromX), round(m_fromY), round(pixVector.x), round(pixVector.y));
    painter->drawLine(line);
}

void VectorPainter::drawArrowHead(QPainter *painter, int idx)
{
    painter->setPen(QPen(m_vectorColor[idx], 0/*getVectorLineWidth(painter)*/));
    PixelVector pixVector = calcPixVec(painter, idx);

    const float angle = atan2(pixVector.y - m_fromY , pixVector.x - m_fromX);
    constexpr float arrowWidth = M_PI * 0.125;
    const float arrowHeight = getArrowHeight(painter);
    QVector<QPoint> points = {
        QPoint(round(pixVector.x), round(pixVector.y)),
        QPoint(round(pixVector.x - arrowHeight * cos(angle - arrowWidth)), round(pixVector.y - arrowHeight * sin(angle - arrowWidth))),
        QPoint(round(pixVector.x - arrowHeight * cos(angle + arrowWidth)), round(pixVector.y - arrowHeight * sin(angle + arrowWidth))),
    };

    QBrush brush;
    brush.setColor(m_vectorColor[idx]);
    brush.setStyle(Qt::SolidPattern);

    QPolygon poly(points);
    painter->drawPolygon(poly);
    QPainterPath path;
    path.addPolygon(poly);

    painter->fillPath(path, brush);
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

float VectorPainter::getNominalUOrI(int idx)
{
    if (idx < COUNT_PHASES)
        return m_nomVoltage;
    return m_nomCurrent;
}

float VectorPainter::getMinimalUOrI(int idx)
{
    if (idx < COUNT_PHASES)
        return m_minVoltage;
    return m_minCurrent;
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

float VectorPainter::getVectorLineWidth(const QPainter *painter)
{
    return getClipSquareLen(painter) * 0.01; // to be adjusted...
}

float VectorPainter::getVectorLenMaxInPixels(const QPainter *painter)
{
    constexpr float totalLenAvail = 1.0;
    constexpr float extraLabelLenFromAvail = 0.2;
    constexpr float vectorLenFromAvail = totalLenAvail - extraLabelLenFromAvail;

    const float pixelsAvailforVector = getClipSquareLen(painter) / 2 * vectorLenFromAvail;
    return pixelsAvailforVector;
}

float VectorPainter::getVectorLenNominalInPixels(const QPainter *painter)
{
    return getVectorLenMaxInPixels(painter) / m_maxOvershoot;
}

float VectorPainter::getArrowHeight(const QPainter *painter)
{
    return getClipSquareLen(painter) * 0.03;
}

void VectorPainter::setFontForLabels(QPainter *painter)
{
    const int minXy = std::min(height(painter), width(painter));
    QFont defaultFont;
    defaultFont.setPixelSize(minXy > 0.0 ? minXy / 25 : 10.0);
    defaultFont.setFamily("Sans");
    painter->setFont(defaultFont);
}

VectorPainter::PixelVector VectorPainter::calcPixVec(QPainter *painter, int idx, float shortenPixels)
{
    const QVector2D vector = m_vector[idx];
    const float tmpPhi = atan2(vector.y(), vector.x()) - m_phiOrigin;
    const float nomValue = getNominalUOrI(idx);
    const float nomRadius = getVectorLenNominalInPixels(painter);
    const float vectLenPixels = nomRadius * vector.length() / nomValue - shortenPixels;
    PixelVector pixVector;
    pixVector.x = m_fromX + vectLenPixels * cos(tmpPhi);
    pixVector.y = m_fromY + vectLenPixels * sin(tmpPhi);
    return pixVector;
}
