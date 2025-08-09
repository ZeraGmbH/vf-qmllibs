#include "vectorpaintcontroller.h"
#include "vectorpaintcalc.h"
#include <QGradient>
#include <QPainterPath>
#include <QMultiMap>
#include <math.h>

void VectorPaintController::setMaxOvershootFactor(float maxOvershoot)
{
    m_vectorSettingsLengths.setMaxOvershoot(maxOvershoot);
}

void VectorPaintController::setNominalVoltage(float nomVoltage)
{
    m_vectorSettingsLengths.setNomVoltage(nomVoltage);
}

void VectorPaintController::setMinVoltage(float minVoltage)
{
    m_vectorSettingsLengths.setMinVoltage(minVoltage);
}

void VectorPaintController::setNominalCurrent(float nomCurrent)
{
    m_vectorSettingsLengths.setNomCurrent(nomCurrent);
}

void VectorPaintController::setMinCurrent(float minCurrent)
{
    m_vectorSettingsLengths.setMinCurrent(minCurrent);
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
    VectorSettingsStatic::setFontForLabels(painter);
    drawGrid(painter);
    drawCircle(painter);

    for(int idx=0; idx<VectorSettingsStatic::COUNT_VECTORS; ++idx) {
        if (m_vector[idx].length() > m_vectorSettingsLengths.getMinimalUOrI(idx)) {
            const float nomValue = m_vectorSettingsLengths.getNominalUOrI(idx);
            drawVectorLine(painter, nomValue, m_vector[idx], m_vectorColor[idx]);
            drawArrowHead(painter, nomValue, m_vector[idx], m_vectorColor[idx]);
        }
    }
}

void VectorPaintController::drawGrid(QPainter *painter)
{
    if(!m_gridVisible)
        return;
    painter->setPen(QPen(m_gridColor, VectorSettingsStatic::getGridAndCircleLineWidth(painter)));
    const float lenFromCenter = VectorPaintCalc::getClipSquareLen(painter) / 2;
    const float centerX = VectorPaintCalc::centerX(painter);
    const float centerY = VectorPaintCalc::centerY(painter);
    painter->drawLine(round(centerX-lenFromCenter), round(centerY),
                      round(centerX+lenFromCenter), round(centerY)); // x axis
    painter->drawLine(round(centerX), round(centerY-lenFromCenter),
                      round(centerX), round(centerY+lenFromCenter)); // y axis
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
    float lineWidth = VectorSettingsStatic::getGridAndCircleLineWidth(painter);
    painter->setPen(QPen(m_circleColor, lineWidth));
    const float radius = m_vectorSettingsLengths.getVectorLenNominalInPixels(painter);
    QRect circleRect(
        round(VectorPaintCalc::centerX(painter) - radius),
        round(VectorPaintCalc::centerY(painter) - radius),
        round(2 * radius),
        round(2 * radius));
    painter->drawArc(circleRect, 0, 16*360);
}

void VectorPaintController::drawVectorLine(QPainter *painter, float nomValue, const QVector2D &value, const QColor &color)
{
    const float lineWidth = VectorSettingsStatic::getVectorLineWidth(painter);
    painter->setPen(QPen(color, lineWidth));
    // still overlap lineWidth/2 caused by line end
    QVector2D vectorFull = calcPixVec(painter, nomValue, value, VectorSettingsStatic::getArrowHeight(painter));
    QVector2D vectorKeepOut = VectorPaintCalc::calcVectorOtherLen(vectorFull, lineWidth / 2);
    const float centerX = VectorPaintCalc::centerX(painter);
    const float centerY = VectorPaintCalc::centerY(painter);
    QLine line(round(centerX + vectorKeepOut.x()), round(centerY + vectorKeepOut.y()),
               round(centerX + vectorFull.x()), round(centerY + vectorFull.y()));
    painter->drawLine(line);
}

void VectorPaintController::drawArrowHead(QPainter *painter, float nomValue, const QVector2D &value, const QColor &color)
{
    painter->setPen(QPen(color, 0));
    const QVector2D pixVector = calcPixVec(painter, nomValue, value);
    const float angle = atan2(pixVector.y(), pixVector.x());
    const float arrowWidth = VectorSettingsStatic::getArrowSpreadAngle();
    const float arrowHeight = VectorSettingsStatic::getArrowHeight(painter);
    const float centerX = VectorPaintCalc::centerX(painter);
    const float centerY = VectorPaintCalc::centerY(painter);
    const QVector2D centeredVector = pixVector + QVector2D(centerX, centerY);
    QVector<QPoint> points = {
        QPoint(round(centeredVector.x()),
               round(centeredVector.y())),
        QPoint(round(centeredVector.x() - arrowHeight * cos(angle - arrowWidth)),
               round(centeredVector.y() - arrowHeight * sin(angle - arrowWidth))),
        QPoint(round(centeredVector.x() - arrowHeight * cos(angle + arrowWidth)),
               round(centeredVector.y() - arrowHeight * sin(angle + arrowWidth))),
    };

    QBrush brush;
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);

    QPolygon poly(points);
    painter->drawPolygon(poly);
    QPainterPath path;
    path.addPolygon(poly);

    painter->fillPath(path, brush);
}

QVector2D VectorPaintController::calcPixVec(QPainter *painter, float nomValue, const QVector2D &value, float shortenPixels)
{
    const float angle = atan2(value.y(), value.x()) + m_vectorSettingsAngles.getOffsetAngle();
    const float nomRadius = m_vectorSettingsLengths.getVectorLenNominalInPixels(painter);
    const float vectLenPixels = nomRadius * value.length() / nomValue - shortenPixels;
    QVector2D resultVector(
        vectLenPixels * cos(angle),
        vectLenPixels * sin(angle));
    return resultVector;
}
