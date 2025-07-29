#include "vectorpainter.h"
#include <QGradient>
#include <QPainterPath>
#include <math.h>

void VectorPainter::setFromX(const float &fromX)
{
    m_fromX = fromX;
}

void VectorPainter::setFromY(const float &fromY)
{
    m_fromY = fromY;
}

void VectorPainter::setPhiOrigin(const float &phiOrigin)
{
    m_phiOrigin = phiOrigin;
}

void VectorPainter::setGridScale(float gridScale)
{
    m_gridScale = gridScale;
}

void VectorPainter::setMaxVoltage(float maxVoltage)
{
    m_maxVoltage = maxVoltage;
}

void VectorPainter::setGridVisible(bool gridVisible)
{
    m_gridVisible = gridVisible;
}

void VectorPainter::setCircleVisible(bool circleVisible)
{
    m_circleVisible = circleVisible;
}

void VectorPainter::setCircleValue(float circleValue)
{
    m_circleValue = circleValue;
}

float VectorPainter::pixelScale(QPainter *painter, float base)
{
    return std::min(height(painter), width(painter))/base/2;
}

void VectorPainter::drawCenterPoint(QPainter *painter)
{
    painter->setPen(QPen(Qt::gray, 2));
    painter->drawPoint(m_fromX, m_fromY);
}

void VectorPainter::drawLabel(QPainter *painter, const QString &label, const QFont &font, float vectorPhi, QColor color, float scale, float labelPhiOffset)
{
    QFontMetrics fontMetrics(font);
    int xOffset = fontMetrics.horizontalAdvance(label) / 2;

    const float tmpPhi = vectorPhi - m_phiOrigin;
    constexpr float maxPhi = 0.25;
    if(fabs(labelPhiOffset) > maxPhi) {
        if(labelPhiOffset > 0)
            labelPhiOffset = maxPhi;
        else
            labelPhiOffset = -maxPhi;
    }
    float xPos = m_fromX - xOffset + scale * m_gridScale * m_circleValue * 1.2 * cos(tmpPhi + labelPhiOffset);
    float yPos = m_fromY + 5 + 0.9 * scale * m_gridScale * m_circleValue * 1.2 * sin(tmpPhi + labelPhiOffset);

    painter->setPen(QPen(color, 2));
    painter->setFont(font);
    painter->drawText(round(xPos), round(yPos),label);
}

void VectorPainter::drawArrowHead(QPainter *painter, QVector2D vector, QColor color, float maxValue)
{
    painter->setPen(QPen(color, 2));
    float arrowHeadSize = height(painter) / 35;

    const float tmpPhi = atan2(vector.y(), vector.x()) - m_phiOrigin;
    const float tmpToX = m_fromX + pixelScale(painter, maxValue) * vector.length() * cos(tmpPhi);
    const float tmpToY = m_fromY + pixelScale(painter, maxValue) * vector.length() * sin(tmpPhi);

    const float angle = atan2(tmpToY - m_fromY , tmpToX - m_fromX);
    if((pixelScale(painter, maxValue) * vector.length()) != 0){
        QVector<QPoint> points = {
            QPoint(roundf(tmpToX), roundf(tmpToY)),
            QPoint(roundf(tmpToX - arrowHeadSize * cos(angle - M_PI / 8)), roundf(tmpToY - arrowHeadSize * sin(angle - M_PI / 8))),
            QPoint(roundf(tmpToX - arrowHeadSize * cos(angle + M_PI / 8)), roundf(tmpToY - arrowHeadSize * sin(angle + M_PI / 8))),
        };

        QPolygon poly(points);

        painter->drawPolygon(poly);

        QBrush brush;
        brush.setColor(color);
        brush.setStyle(Qt::SolidPattern);

        QPainterPath path;
        path.addPolygon(poly);

        painter->fillPath(path, brush);
    }
}

float VectorPainter::labelVectorLen(float screenLen)
{
    // limit labels out of range
    float labelLen = screenLen * 1.25;
    if(labelLen > 1.1)
        return 1.1;
    // avoid crowded center
    if(labelLen < 0.4)
        return 0.4;
    return labelLen;
}

void VectorPainter::drawGridAndCircle(QPainter *painter)
{
    constexpr double radiusWidth = 1.5;
    painter->setPen(QPen(Qt::darkGray, radiusWidth));

    //grid
    if(m_gridVisible) {
        //x axis
        painter->drawLine(m_fromX - m_maxVoltage * m_gridScale, m_fromY, m_fromX + m_maxVoltage * m_gridScale, m_fromY);

        //y axis
        painter->drawLine(m_fromX, m_fromY - m_maxVoltage * m_gridScale, m_fromX, m_fromY + m_maxVoltage * m_gridScale);
    }

    //circle
    if(m_circleVisible) {
        painter->drawArc(
            m_fromX-(m_gridScale * m_circleValue)-radiusWidth,
            m_fromY-(m_gridScale * m_circleValue)-radiusWidth,
            2 * (m_gridScale * m_circleValue + radiusWidth),
            2 * (m_gridScale * m_circleValue + radiusWidth),
            0, 5760);
    }
}

void VectorPainter::drawVectorLine(QPainter *painter, QVector2D vector, QColor color, float maxValue)
{
    painter->setPen(QPen(color, 2));
    const float tmpPhi = atan2(vector.y(), vector.x()) - m_phiOrigin;
    const float tmpX = m_fromX + pixelScale(painter, maxValue) * vector.length() * cos(tmpPhi);
    const float tmpY = m_fromY + pixelScale(painter, maxValue) * vector.length() * sin(tmpPhi);
    painter->drawLine(roundf(m_fromX), roundf(m_fromY), roundf(tmpX), roundf(tmpY));
}

int VectorPainter::height(QPainter *painter)
{
    QPaintDevice *paintDevice = painter->device();
    if (paintDevice)
        return paintDevice->height();
    return 1;
}

int VectorPainter::width(QPainter *painter)
{
    QPaintDevice *paintDevice = painter->device();
    if (paintDevice)
        return paintDevice->width();
    return 1;
}

