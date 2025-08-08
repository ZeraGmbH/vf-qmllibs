#include "vectorpaintcontroller.h"
#include <QFont>
#include <QGradient>
#include <QPainterPath>
#include <QMultiMap>
#include <math.h>

void VectorPaintController::setMaxOvershootFactor(float maxOvershoot)
{
    m_maxOvershoot = maxOvershoot;
}

void VectorPaintController::setNominalVoltage(float nomVoltage)
{
    m_nomVoltage = nomVoltage;
}

void VectorPaintController::setMinVoltage(float minVoltage)
{
    m_minVoltage = minVoltage;
}

void VectorPaintController::setNominalCurrent(float nomCurrent)
{
    m_nomCurrent = nomCurrent;
}

void VectorPaintController::setMinCurrent(float minCurrent)
{
    m_minCurrent = minCurrent;
}

void VectorPaintController::setVectorType(VectorType vectorType)
{
    m_vectorType = vectorType;
}

void VectorPaintController::setGridVisible(bool gridVisible)
{
    m_gridVisible = gridVisible;
}

void VectorPaintController::setGridColor(const QColor &gridColor)
{
    m_gridColor = gridColor;
}

void VectorPaintController::setCircleVisible(bool circleVisible)
{
    m_circleVisible = circleVisible;
}

void VectorPaintController::setCircleColor(const QColor &circleColor)
{
    m_circleColor = circleColor;
}

void VectorPaintController::setVector(int idx, const QVector2D &vector)
{
    m_vector[idx] = vector;
}

void VectorPaintController::setVectorColor(int idx, const QColor &vectorColor)
{
    m_vectorColor[idx] = vectorColor;
}

void VectorPaintController::setVectorLabel(int idx, const QString &vectorLabel)
{
    m_vectorLabel[idx] = vectorLabel;
}

void VectorPaintController::paint(QPainter *painter)
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

void VectorPaintController::drawGrid(QPainter *painter)
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


void VectorPaintController::drawCircle(QPainter *painter)
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

void VectorPaintController::drawVectorLine(QPainter *painter, int idx)
{
    const float lineWidth = getVectorLineWidth(painter);
    painter->setPen(QPen(m_vectorColor[idx], lineWidth));
    QVector2D vectorFull = calcPixVec(painter, idx, getArrowHeight(painter)); // still overlap lineWidth/2
    QVector2D vectorKeepOut = calcVectorOtherLen(vectorFull, lineWidth / 2);
    QLine line(round(m_fromX + vectorKeepOut.x()), round(m_fromY + vectorKeepOut.y()),
               round(m_fromX + vectorFull.x()), round(m_fromY + vectorFull.y()));
    painter->drawLine(line);
}

void VectorPaintController::drawArrowHead(QPainter *painter, int idx)
{
    painter->setPen(QPen(m_vectorColor[idx], 0));
    const QVector2D pixVector = calcPixVec(painter, idx);
    const float angle = atan2(pixVector.y(), pixVector.x());
    constexpr float arrowWidth = M_PI * 0.125;
    const float arrowHeight = getArrowHeight(painter);
    const QVector2D vectorMoved = pixVector + QVector2D(m_fromX, m_fromY);
    QVector<QPoint> points = {
        QPoint(round(vectorMoved.x()), round(vectorMoved.y())),
        QPoint(round(vectorMoved.x() - arrowHeight * cos(angle - arrowWidth)), round(vectorMoved.y() - arrowHeight * sin(angle - arrowWidth))),
        QPoint(round(vectorMoved.x() - arrowHeight * cos(angle + arrowWidth)), round(vectorMoved.y() - arrowHeight * sin(angle + arrowWidth))),
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

int VectorPaintController::height(const QPainter *painter)
{
    QPaintDevice *paintDevice = painter->device();
    if (paintDevice)
        return paintDevice->height();
    return 1;
}

int VectorPaintController::width(const QPainter *painter)
{
    QPaintDevice *paintDevice = painter->device();
    if (paintDevice)
        return paintDevice->width();
    return 1;
}

float VectorPaintController::getNominalUOrI(int idx)
{
    if (idx < COUNT_PHASES)
        return m_nomVoltage;
    return m_nomCurrent;
}

float VectorPaintController::getMinimalUOrI(int idx)
{
    if (idx < COUNT_PHASES)
        return m_minVoltage;
    return m_minCurrent;
}

float VectorPaintController::getClipSquareLen(const QPainter *painter)
{
    const float w = width(painter);
    const float h = height(painter);
    return std::min(h, w);
}

float VectorPaintController::getGridAndCircleLineWidth(const QPainter *painter)
{
    return getClipSquareLen(painter) * 0.005; // to be adjusted...
}

float VectorPaintController::getVectorLineWidth(const QPainter *painter)
{
    return getClipSquareLen(painter) * 0.01; // to be adjusted...
}

float VectorPaintController::getVectorLenMaxInPixels(const QPainter *painter)
{
    constexpr float totalLenAvail = 1.0;
    constexpr float extraLabelLenFromAvail = 0.2;
    constexpr float vectorLenFromAvail = totalLenAvail - extraLabelLenFromAvail;

    const float pixelsAvailforVector = getClipSquareLen(painter) / 2 * vectorLenFromAvail;
    return pixelsAvailforVector;
}

float VectorPaintController::getVectorLenNominalInPixels(const QPainter *painter)
{
    return getVectorLenMaxInPixels(painter) / m_maxOvershoot;
}

float VectorPaintController::getArrowHeight(const QPainter *painter)
{
    return getClipSquareLen(painter) * 0.03;
}

void VectorPaintController::setFontForLabels(QPainter *painter)
{
    const int minXy = std::min(height(painter), width(painter));
    QFont defaultFont;
    defaultFont.setPixelSize(minXy > 0.0 ? minXy / 25 : 10.0);
    defaultFont.setFamily("Sans");
    painter->setFont(defaultFont);
}

QVector2D VectorPaintController::calcPixVec(QPainter *painter, int idx, float shortenPixels)
{
    const QVector2D vector = m_vector[idx];
    const float tmpPhi = atan2(vector.y(), vector.x()) - m_phiOrigin;
    const float nomValue = getNominalUOrI(idx);
    const float nomRadius = getVectorLenNominalInPixels(painter);
    const float vectLenPixels = nomRadius * vector.length() / nomValue - shortenPixels;
    QVector2D resultVector(
        vectLenPixels * cos(tmpPhi),
        vectLenPixels * sin(tmpPhi));
    return resultVector;
}

QVector2D VectorPaintController::calcVectorOtherLen(const QVector2D &vector, float len)
{
    const float origLen = vector.length();
    const float mult = len / origLen;
    QVector2D resultVector(
        vector.x() * mult,
        vector.y() * mult);
    return resultVector;
}
