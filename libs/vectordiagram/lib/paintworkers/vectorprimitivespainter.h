#ifndef VECTORPRIMITIVESPAINTER_H
#define VECTORPRIMITIVESPAINTER_H

#include "vectorsettingslayout.h"
#include "vectorsettingslengths.h"
#include <QPainter>
#include <QColor>
#include <QVector2D>
#include <QPolygonF>

class VectorPrimitivesPainter
{
public:
    static void drawCoordCross(QPainter *painter, const VectorSettingsLayout &layout);
    static void drawCoordCenterDot(QPainter *painter, const VectorSettingsLayout &layout);
    static void drawCircle(QPainter *painter, const VectorSettingsLengths &lengths, const VectorSettingsLayout &layout);
    struct VectorParam
    {
        PhaseType phaseType;
        QVector2D pixLenVector;
        QColor color;
    };
    static void drawVector(QPainter *painter, const VectorParam &vectorParam, const VectorSettingsLayout &layout);
    static void drawTriangle(QPainter *painter,
                             const VectorParam &vectorParam1, const VectorParam &vectorParam2, const VectorParam &vectorParam3,
                             const VectorSettingsLayout &layout);
    static void drawLabel(QPainter *painter, const VectorParam &vectorParam, const QFont& labelFont, const QString &label);
private:
    static void drawVectorLine(QPainter *painter, const VectorParam &vectorParam, const VectorSettingsLayout &layout);
    static void drawArrowHead(QPainter *painter, const VectorParam &vectorParam, const VectorSettingsLayout &layout);
    struct PointData {
        QPointF point;
        QColor color;
    };
    static void drawGradientLine(QPainter *painter, const float lineWidth,
                                 const PointData &pt1, const PointData &pt2);
    static QPolygonF lineToRectangleForSvgGradient(const QLineF &line, float width,
                                                   float shortenBothEnds = 0);
};

#endif // VECTORPRIMITIVESPAINTER_H
