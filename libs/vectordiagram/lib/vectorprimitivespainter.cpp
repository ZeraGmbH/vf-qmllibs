#include "vectorprimitivespainter.h"
#include "vectorsettingsstatic.h"
#include "vectorpaintcalc.h"
#include <QGradient>
#include <QPainterPath>

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

void VectorPrimitivesPainter::drawVector(QPainter *painter, const VectorParam &vectorParam, float lineWidth)
{
    drawVectorLine(painter, vectorParam, lineWidth);
    drawArrowHead(painter, vectorParam);
}

void VectorPrimitivesPainter::drawTriangle(QPainter *painter, const GeometryParam &geomParam,
                                           const VectorData &vector1,
                                           const VectorData &vector2,
                                           const VectorData &vector3)
{
    // positions
    const QVector<VectorData> vectors{vector1, vector2, vector3};
    QVector<QPoint> positions(VectorSettingsStatic::COUNT_PHASES);
    const float lineWidth = VectorSettingsStatic::getVectorLineWidth(painter);
    for (int phase=0; phase<VectorSettingsStatic::COUNT_PHASES; phase++) {
        QVector2D vector = VectorPaintCalc::calcPixVec(painter, geomParam, vectors[phase].value);
        const float centerX = VectorPaintCalc::centerX(painter);
        const float centerY = VectorPaintCalc::centerY(painter);
        positions[phase] = QPoint(round(centerX+vector.x()), round(centerY+vector.y()));
    }

    // 1 -> 2
    drawGradientLine(painter, lineWidth, {positions[0], vector1.color}, {positions[1], vector2.color});
    // 2 -> 3
    drawGradientLine(painter, lineWidth, {positions[1], vector2.color}, {positions[2], vector3.color});
    // 3 -> 1
    drawGradientLine(painter, lineWidth, {positions[2], vector3.color}, {positions[0], vector1.color});
}

void VectorPrimitivesPainter::drawVectorLine(QPainter *painter, const VectorParam &vectorParam, float lineWidth)
{
    painter->setPen(QPen(vectorParam.color, lineWidth));
    // still overlap lineWidth/2 caused by line end
    QVector2D vectorShortened = VectorPaintCalc::calcVectorOtherLen(
        vectorParam.pixLenVector,
        vectorParam.pixLenVector.length() - VectorSettingsStatic::getArrowHeight(painter));
    QVector2D vectorKeepOut = VectorPaintCalc::calcVectorOtherLen(vectorShortened, lineWidth / 2);
    const float centerX = VectorPaintCalc::centerX(painter);
    const float centerY = VectorPaintCalc::centerY(painter);
    QLine line(round(centerX + vectorKeepOut.x()), round(centerY + vectorKeepOut.y()),
               round(centerX + vectorShortened.x()), round(centerY + vectorShortened.y()));
    painter->drawLine(line);
}

void VectorPrimitivesPainter::drawArrowHead(QPainter *painter, const VectorParam &vectorParam)
{
    painter->setPen(QPen(vectorParam.color, 0));
    const float angle = atan2(vectorParam.pixLenVector.y(), vectorParam.pixLenVector.x());
    const float arrowWidth = VectorSettingsStatic::getArrowSpreadAngle();
    const float arrowHeight = VectorSettingsStatic::getArrowHeight(painter);
    const float centerX = VectorPaintCalc::centerX(painter);
    const float centerY = VectorPaintCalc::centerY(painter);
    const QVector2D centeredVector = vectorParam.pixLenVector + QVector2D(centerX, centerY);
    QVector<QPoint> points = {
        QPoint(round(centeredVector.x()),
               round(centeredVector.y())),
        QPoint(round(centeredVector.x() - arrowHeight * cos(angle - arrowWidth)),
               round(centeredVector.y() - arrowHeight * sin(angle - arrowWidth))),
        QPoint(round(centeredVector.x() - arrowHeight * cos(angle + arrowWidth)),
               round(centeredVector.y() - arrowHeight * sin(angle + arrowWidth))),
    };

    QBrush brush;
    brush.setColor(vectorParam.color);
    brush.setStyle(Qt::SolidPattern);

    QPolygon poly(points);
    painter->drawPolygon(poly);
    QPainterPath path;
    path.addPolygon(poly);

    painter->fillPath(path, brush);
}

void VectorPrimitivesPainter::drawGradientLine(QPainter *painter, const float lineWidth,
                                               const PointData &pt1, const PointData &pt2)
{
    // Lines with gradients are painted black on SVG.
    // Work around by drawing lines as rectangles (polygon)
    QLinearGradient grad(pt1.point, pt2.point);
    grad.setColorAt(0, pt1.color);
    grad.setColorAt(1, pt2.color);
    painter->setBrush(grad);
    painter->setPen(Qt::NoPen);

    QPolygonF polyRect = lineToRectangleForSvgGradient(QLineF(pt1.point, pt2.point), lineWidth, lineWidth/2);
    painter->drawPolygon(polyRect);

    // Draw rounded caps
    QPointF p1 = polyRect[1];
    QPointF p2 = polyRect[2];
    QLineF l1(p1, p2);
    QPointF center1 = l1.center();
    painter->drawEllipse(center1, lineWidth/2, lineWidth/2);

    QPointF p0 = polyRect[0];
    QPointF p3 = polyRect[3];
    QLineF l2(p0, p3);
    QPointF center2 = l2.center();
    painter->drawEllipse(center2, lineWidth/2, lineWidth/2);
}

QPolygonF VectorPrimitivesPainter::lineToRectangleForSvgGradient(const QLineF &line, float width,
                                                                 float shortenBothEnds)
{
    const QPointF &start = line.p1();
    const QPointF &end = line.p2();
    // Calculate the direction vector
    QPointF direction = end - start;

    // Get the normalized perpendicular vector (for width offset)
    QPointF norm = QPointF(-direction.y(), direction.x());
    norm /= std::sqrt(norm.x()*norm.x() + norm.y()*norm.y()); // normalize
    norm *= (width/2.0);

    // len offset
    QPointF shortPt = QPointF(direction.x(), direction.y());
    shortPt /= std::sqrt(shortPt.x()*shortPt.x() + shortPt.y()*shortPt.y()); // normalize
    shortPt *= (shortenBothEnds);

    // Rectangle corners (counter-clockwise or clockwise)
    QPointF corner1 = start + norm + shortPt;
    QPointF corner2 = end + norm - shortPt;
    QPointF corner3 = end - norm - shortPt;
    QPointF corner4 = start - norm + shortPt;
    QPolygonF polygon;
    polygon << corner1 << corner2 << corner3 << corner4;
    return polygon;
}
