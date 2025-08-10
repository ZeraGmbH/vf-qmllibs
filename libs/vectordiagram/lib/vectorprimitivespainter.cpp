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
                                         float nominalValue, const VectorData &vector)
{
    drawVectorLine(painter, geomSetttings, nominalValue, vector);
    drawArrowHead(painter, geomSetttings, nominalValue, vector);
}

void VectorPrimitivesPainter::drawTriangle(QPainter *painter, const VectorSettingsGeometry &geomSetttings,
                                           float nominalValue,
                                           const VectorData &vector1, const VectorData &vector2, const VectorData &vector3)
{
    // positions
    const QVector<VectorData> vectors{vector1, vector2, vector3};
    QVector<QPoint> positions(VectorSettingsStatic::COUNT_PHASES);
    for (int phase=0; phase<VectorSettingsStatic::COUNT_PHASES; phase++) {
        QVector2D vector = calcPixVec(painter, geomSetttings,
                                    nominalValue, vectors[phase].value);
        const float centerX = VectorPaintCalc::centerX(painter);
        const float centerY = VectorPaintCalc::centerY(painter);
        positions[phase] = QPoint(round(centerX+vector.x()), round(centerY+vector.y()));
    }

    // gradients
    // 1 -> 2
    QLinearGradient grd1(positions[0], positions[1]);
    grd1.setColorAt(0, vector1.color);
    grd1.setColorAt(1, vector2.color);
    // 2 -> 3
    QLinearGradient grd2(positions[1], positions[2]);
    grd2.setColorAt(0, vector2.color);
    grd2.setColorAt(1, vector3.color);
    // 3 -> 1
    QLinearGradient grd3(positions[2], positions[0]);
    grd3.setColorAt(0, vector3.color);
    grd3.setColorAt(1, vector1.color);

    // Lines with gradients are painted black on SVG.
    // Work around by drawing lines as rectangles (polygon)
    const float lineWidth = VectorSettingsStatic::getVectorLineWidth(painter);
    painter->setPen(Qt::NoPen);
    // 1 -> 2
    QPolygonF rect12 = lineToRectangleForSvgGradient(positions[0], positions[1], lineWidth);
    painter->setBrush(grd1);
    painter->drawPolygon(rect12);
    // 2 -> 3
    QPolygonF rect23 = lineToRectangleForSvgGradient(positions[1], positions[2], lineWidth);
    painter->setBrush(grd2);
    painter->drawPolygon(rect23);
    // 3 -> 1
    QPolygonF rect31 = lineToRectangleForSvgGradient(positions[2], positions[0], lineWidth);
    painter->setBrush(grd3);
    painter->drawPolygon(rect31);
}

void VectorPrimitivesPainter::drawVectorLine(QPainter *painter, const VectorSettingsGeometry &geomSetttings,
                                             float nominalValue, const VectorData &vector)
{
    const float lineWidth = VectorSettingsStatic::getVectorLineWidth(painter);
    painter->setPen(QPen(vector.color, lineWidth));
    // still overlap lineWidth/2 caused by line end
    QVector2D vectorFull = calcPixVec(painter, geomSetttings,
                                      nominalValue, vector.value, VectorSettingsStatic::getArrowHeight(painter));
    QVector2D vectorKeepOut = VectorPaintCalc::calcVectorOtherLen(vectorFull, lineWidth / 2);
    const float centerX = VectorPaintCalc::centerX(painter);
    const float centerY = VectorPaintCalc::centerY(painter);
    QLine line(round(centerX + vectorKeepOut.x()), round(centerY + vectorKeepOut.y()),
               round(centerX + vectorFull.x()), round(centerY + vectorFull.y()));
    painter->drawLine(line);
}

void VectorPrimitivesPainter::drawArrowHead(QPainter *painter, const VectorSettingsGeometry &geomSetttings,
                                            float nominalValue, const VectorData &vector)
{
    painter->setPen(QPen(vector.color, 0));
    const QVector2D pixVector = calcPixVec(painter, geomSetttings, nominalValue, vector.value);
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
    brush.setColor(vector.color);
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
        // y on screen increases downwards => Mathematical <=> -1.0
        geomSetttings.m_angles.getRotationDirection() == VectorSettingsAngles::Mathematical ? -1.0 : 1.0;
    QVector2D resultVector(
        vectLenPixels * cos(angle),
        vectLenPixels * sin(angle) * directionFactor);
    return resultVector;
}

QPolygonF VectorPrimitivesPainter::lineToRectangleForSvgGradient(const QPoint &start, const QPoint &end, int width)
{
    // Calculate the direction vector
    QLineF line(start, end);
    QPointF direction = line.p2() - line.p1();

    // Get the normalized perpendicular vector (for width offset)
    QPointF norm = QPointF(-direction.y(), direction.x());
    norm /= std::sqrt(norm.x()*norm.x() + norm.y()*norm.y()); // normalize
    norm *= (width/2.0);

    // Rectangle corners (counter-clockwise or clockwise)
    QPointF corner1 = QPointF(start) + norm;
    QPointF corner2 = QPointF(end) + norm;
    QPointF corner3 = QPointF(end) - norm;
    QPointF corner4 = QPointF(start) - norm;
    QPolygonF polygon;
    polygon << corner1 << corner2 << corner3 << corner4;
    return polygon;
}
