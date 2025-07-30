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

void VectorPainter::setMinVoltage(float minVoltage)
{
    m_minVoltage = minVoltage;
}

void VectorPainter::setMaxCurrent(float maxCurrent)
{
    m_maxCurrent = maxCurrent;
}

void VectorPainter::setMinCurrent(float minCurrent)
{
    m_minCurrent = minCurrent;
}

void VectorPainter::setVectorView(VectorView vectorView)
{
    m_vectorView = vectorView;
}

void VectorPainter::setMaxValueVoltage(float maxValueVoltage)
{
    m_maxValueVoltage = maxValueVoltage;
}

void VectorPainter::setMaxValueCurrent(float maxValueCurrent)
{
    m_maxValueCurrent = maxValueCurrent;
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

void VectorPainter::setCircleValue(float circleValue)
{
    m_circleValue = circleValue;
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
    m_SetUCollisions.clear();

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

void VectorPainter::drawLabel(QPainter *painter,
                              int idx,
                              const QFont &font,
                              float scale,
                              float labelPhiOffset)
{
    QFontMetrics fontMetrics(font);
    const QString& label = m_vectorLabel[idx];
    int xOffset = fontMetrics.horizontalAdvance(label) / 2;

    const float vectorPhi = atan2(m_vector[idx].y(), m_vector[idx].x());
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

    painter->setPen(QPen(m_vectorColor[idx], 2));
    painter->setFont(font);
    painter->drawText(round(xPos), round(yPos), label);
}

void VectorPainter::drawArrowHead(QPainter *painter, int idx, float maxValue)
{
    const QColor &color = m_vectorColor[idx];
    painter->setPen(QPen(color, 2));
    float arrowHeadSize = height(painter) / 35;

    const QVector2D vector = m_vector[idx];
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

float VectorPainter::detectCollision(int uPhase)
{
    // check collision with I vectors
    QVector2D vectors[] = { m_vector[3], m_vector[4], m_vector[5] };
    for(int idx = 0; idx<COUNT_PHASES; ++idx) {
        QVector2D vectorI = vectors[idx];
        // compare angles
        QVector2D vectorIScreen = vectorI / m_maxCurrent;
        QVector2D vectorUScreen = m_vectorUScreen[uPhase];
        float angleI = atan2(vectorIScreen.y() , vectorIScreen.x());
        float angleU = atan2(vectorUScreen.y() , vectorUScreen.x());
        float diffAngle = fabs(angleU - angleI);
        if(angleU > angleI && diffAngle < 0.7) {
            m_SetUCollisions.insert(idx);
            return -1.0;
        }
    }
    return 1.0;
}

void VectorPainter::drawGridAndCircle(QPainter *painter)
{
    constexpr double radiusWidth = 1.5;
    //grid
    if(m_gridVisible) {
        painter->setPen(QPen(m_gridColor, radiusWidth));
        //x axis
        painter->drawLine(m_fromX - m_maxVoltage * m_gridScale, m_fromY, m_fromX + m_maxVoltage * m_gridScale, m_fromY);

        //y axis
        painter->drawLine(m_fromX, m_fromY - m_maxVoltage * m_gridScale, m_fromX, m_fromY + m_maxVoltage * m_gridScale);
    }

    //circle
    if(m_circleVisible) {
        painter->setPen(QPen(m_circleColor, radiusWidth));
        painter->drawArc(
            m_fromX-(m_gridScale * m_circleValue)-radiusWidth,
            m_fromY-(m_gridScale * m_circleValue)-radiusWidth,
            2 * (m_gridScale * m_circleValue + radiusWidth),
            2 * (m_gridScale * m_circleValue + radiusWidth),
            0, 5760);
    }
}

void VectorPainter::drawVectorLine(QPainter *painter, int idx, float maxValue)
{
    painter->setPen(QPen(m_vectorColor[idx], 2));
    const QVector2D vector = m_vector[idx];
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

