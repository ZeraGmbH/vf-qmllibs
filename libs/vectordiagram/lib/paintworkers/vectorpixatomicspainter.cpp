#include "vectorpixatomicspainter.h"
#include "vectorconstants.h"
#include "vectorpaintcalc.h"
#include <QGradient>
#include <QPainterPath>

void VectorPixAtomicsPainter::drawCoordCross(QPainter *painter, const VectorSettingsLayout &layout)
{
    painter->setPen(QPen(layout.getCoordCrossColor(), layout.getCoordCrossAndCircleLineWidthPix(painter)));
    const float lenFromCenter = VectorPaintCalc::getClipSquareLen(painter) / 2;
    const float centerX = VectorPaintCalc::centerX(painter);
    const float centerY = VectorPaintCalc::centerY(painter);
    QLineF lineXAxis(centerX-lenFromCenter, centerY, centerX+lenFromCenter, centerY);
    painter->drawLine(lineXAxis);
    QLineF lineYAxis(centerX, centerY-lenFromCenter, centerX, centerY+lenFromCenter);
    painter->drawLine(lineYAxis);
}

void VectorPixAtomicsPainter::drawCoordCenterDot(QPainter *painter, const VectorSettingsLayout &layout)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(layout.getCoordCrossColor());
    const float centerX = VectorPaintCalc::centerX(painter);
    const float centerY = VectorPaintCalc::centerY(painter);
    const float diameter = layout.getCenterDotDiameterPix(painter);
    QPointF center(centerX, centerY);
    painter->drawEllipse(center, diameter/2, diameter/2);
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

void VectorPixAtomicsPainter::drawCircle(QPainter *painter, const VectorSettingsLengths &lengths,
                                         const VectorSettingsLayout &layout)
{
    painter->setPen(QPen(layout.getCircleColor(), layout.getCoordCrossAndCircleLineWidthPix(painter)));
    const float radius = lengths.getVectorLenNominalInPixels(painter);
    QRectF circleRect(
        VectorPaintCalc::centerX(painter) - radius,
        VectorPaintCalc::centerY(painter) - radius,
        2 * radius,
        2 * radius);
    painter->drawArc(circleRect, 0, 16*360);
}

void VectorPixAtomicsPainter::drawVector(QPainter *painter, const VectorParam &vectorParam,
                                         const VectorSettingsLayout &layout)
{
    drawVectorLine(painter, vectorParam, layout);
    drawArrowHead(painter, vectorParam, layout);
}

void VectorPixAtomicsPainter::drawTriangle(QPainter *painter,
                                           const VectorParam &vectorParam1, const VectorParam &vectorParam2, const VectorParam &vectorParam3,
                                           const VectorSettingsLayout &layout)
{
    const QVector<QVector2D> vectors{vectorParam1.pixLenVector, vectorParam2.pixLenVector, vectorParam3.pixLenVector};
    QVector<QPointF> positions(VectorConstants::COUNT_PHASES);
    const float centerX = VectorPaintCalc::centerX(painter);
    const float centerY = VectorPaintCalc::centerY(painter);
    for (int phase=0; phase<VectorConstants::COUNT_PHASES; phase++)
        positions[phase] = QPointF(centerX + vectors[phase].x(), centerY + vectors[phase].y());

    const float lineWidth = layout.getVectorLineWidthPix(painter, PhaseType::TYPE_U);
    // 1 -> 2
    drawGradientLine(painter, lineWidth, {positions[0], vectorParam1.color}, {positions[1], vectorParam2.color});
    // 2 -> 3
    drawGradientLine(painter, lineWidth, {positions[1], vectorParam2.color}, {positions[2], vectorParam3.color});
    // 3 -> 1
    drawGradientLine(painter, lineWidth, {positions[2], vectorParam3.color}, {positions[0], vectorParam1.color});
}

void VectorPixAtomicsPainter::drawLabel(QPainter *painter, const VectorParam &vectorParam, const QFont &labelFont, const QString &label)
{
    painter->setFont(labelFont);
    const float centerX = VectorPaintCalc::centerX(painter);
    const float centerY = VectorPaintCalc::centerY(painter);
    QPointF positionCenter(centerX + vectorParam.pixLenVector.x(), centerY + vectorParam.pixLenVector.y());

    const QPointF textPixSize = VectorPaintCalc::approxFontMetrics(painter, label);
    QPointF positionTopLeft(positionCenter.x()-textPixSize.x(),
                            positionCenter.y()+textPixSize.y());

    painter->setPen(QPen(vectorParam.color, 0));
    painter->drawText(positionTopLeft, label);
}

void VectorPixAtomicsPainter::drawVectorLine(QPainter *painter, const VectorParam &vectorParam,
                                             const VectorSettingsLayout &layout)
{
    const float lineWidth = layout.getVectorLineWidthPix(painter, vectorParam.phaseType);
    painter->setPen(QPen(vectorParam.color, lineWidth));
    QVector2D vectorShortened = VectorPaintCalc::calcVectorOtherLen(
        vectorParam.pixLenVector,
        vectorParam.pixLenVector.length() - layout.getArrowHeightPix(painter, vectorParam.phaseType) - lineWidth / 2);
    QVector2D vectorKeepOut = VectorPaintCalc::calcVectorOtherLen(vectorShortened, lineWidth / 2);
    const float centerX = VectorPaintCalc::centerX(painter);
    const float centerY = VectorPaintCalc::centerY(painter);
    QLineF line(centerX + vectorKeepOut.x(), centerY + vectorKeepOut.y(),
                centerX + vectorShortened.x(), centerY + vectorShortened.y());
    painter->drawLine(line);
}

void VectorPixAtomicsPainter::drawArrowHead(QPainter *painter, const VectorParam &vectorParam,
                                            const VectorSettingsLayout &layout)
{
    painter->setPen(Qt::NoPen);
    const float angle = atan2(vectorParam.pixLenVector.y(), vectorParam.pixLenVector.x());
    const float arrowHeight = layout.getArrowHeightPix(painter, vectorParam.phaseType);
    float arrowSpreadAngle = layout.getArrowSpreadAngle(vectorParam.phaseType);
    const float arrowEffectiveHeight = arrowHeight / cos(arrowSpreadAngle);
    const float centerX = VectorPaintCalc::centerX(painter);
    const float centerY = VectorPaintCalc::centerY(painter);
    const QVector2D centeredVector = vectorParam.pixLenVector + QVector2D(centerX, centerY);
    QVector<QPointF> points = {
        QPointF(centeredVector.x(),
                centeredVector.y()),
        QPointF(centeredVector.x() - arrowEffectiveHeight * cos(angle - arrowSpreadAngle),
                centeredVector.y() - arrowEffectiveHeight * sin(angle - arrowSpreadAngle)),
        QPointF(centeredVector.x() - arrowEffectiveHeight * cos(angle + arrowSpreadAngle),
                centeredVector.y() - arrowEffectiveHeight * sin(angle + arrowSpreadAngle)),
    };

    QBrush brush;
    brush.setColor(vectorParam.color);
    brush.setStyle(Qt::SolidPattern);

    QPolygonF poly(points);
    painter->drawPolygon(poly);
    QPainterPath path;
    path.addPolygon(poly);

    painter->fillPath(path, brush);
}

void VectorPixAtomicsPainter::drawGradientLine(QPainter *painter, const float lineWidth,
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
    if (polyRect.isEmpty())
        return;
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

QPolygonF VectorPixAtomicsPainter::lineToRectangleForSvgGradient(const QLineF &line, float width,
                                                                 float shortenBothEnds)
{
    const QPointF &start = line.p1();
    const QPointF &end = line.p2();
    if (start == end)
        return QPolygonF();

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
