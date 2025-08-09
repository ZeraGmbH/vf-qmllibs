#include "vectorprimitivespainter.h"
#include "vectorsettingsstatic.h"
#include "vectorpaintcalc.h"
#include <QGradient>
#include <QPainterPath>
#include <math.h>

void VectorPrimitivesPainter::drawCoordCross(QPainter *painter, const QColor &color)
{
    painter->setPen(QPen(color, VectorSettingsStatic::getGridAndCircleLineWidth(painter)));
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

void VectorPrimitivesPainter::drawCircle(QPainter *painter, const VectorSettingsLengths &lengths, const QColor &color)
{
    float lineWidth = VectorSettingsStatic::getGridAndCircleLineWidth(painter);
    painter->setPen(QPen(color, lineWidth));
    const float radius = lengths.getVectorLenNominalInPixels(painter);
    QRect circleRect(
        round(VectorPaintCalc::centerX(painter) - radius),
        round(VectorPaintCalc::centerY(painter) - radius),
        round(2 * radius),
        round(2 * radius));
    painter->drawArc(circleRect, 0, 16*360);
}

void VectorPrimitivesPainter::drawVector(QPainter *painter, const VectorSettingsGeometry &geomSetttings,
                                         float nominalValue, const QVector2D &value, const QColor &color)
{
    drawVectorLine(painter, geomSetttings, nominalValue, value, color);
    drawArrowHead(painter, geomSetttings, nominalValue, value, color);
}

void VectorPrimitivesPainter::drawVectorLine(QPainter *painter, const VectorSettingsGeometry &geomSetttings,
                                             float nominalValue, const QVector2D &value, const QColor &color)
{
    const float lineWidth = VectorSettingsStatic::getVectorLineWidth(painter);
    painter->setPen(QPen(color, lineWidth));
    // still overlap lineWidth/2 caused by line end
    QVector2D vectorFull = calcPixVec(painter, geomSetttings,
                                      nominalValue, value, VectorSettingsStatic::getArrowHeight(painter));
    QVector2D vectorKeepOut = VectorPaintCalc::calcVectorOtherLen(vectorFull, lineWidth / 2);
    const float centerX = VectorPaintCalc::centerX(painter);
    const float centerY = VectorPaintCalc::centerY(painter);
    QLine line(round(centerX + vectorKeepOut.x()), round(centerY + vectorKeepOut.y()),
               round(centerX + vectorFull.x()), round(centerY + vectorFull.y()));
    painter->drawLine(line);
}

void VectorPrimitivesPainter::drawArrowHead(QPainter *painter, const VectorSettingsGeometry &geomSetttings,
                                            float nominalValue, const QVector2D &value, const QColor &color)
{
    painter->setPen(QPen(color, 0));
    const QVector2D pixVector = calcPixVec(painter, geomSetttings, nominalValue, value);
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

QVector2D VectorPrimitivesPainter::calcPixVec(QPainter *painter, const VectorSettingsGeometry &geomSetttings,
                                              float nomValue, const QVector2D &value, float shortenPixels)
{
    const float angle = atan2(value.y(), value.x()) + geomSetttings.m_angles.getOffsetAngle();
    const float nomRadius = geomSetttings.m_lengths.getVectorLenNominalInPixels(painter);
    const float vectLenPixels = nomRadius * value.length() / nomValue - shortenPixels;
    const float directionFactor =
        geomSetttings.m_angles.getRotationDirection() == VectorSettingsAngles::Mathematical ? -1.0 : 1.0;
    QVector2D resultVector(
        vectLenPixels * cos(angle),
        vectLenPixels * sin(angle) * directionFactor);
    return resultVector;
}

