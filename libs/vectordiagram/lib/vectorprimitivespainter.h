#ifndef VECTORPRIMITIVESPAINTER_H
#define VECTORPRIMITIVESPAINTER_H

#include "vectorsettingslengths.h"
#include <QPainter>
#include <QColor>
#include <QVector2D>
#include <QPolygonF>

class VectorPrimitivesPainter
{
public:
    static void drawCoordCross(QPainter *painter, const QColor& color);
    static void drawCircle(QPainter *painter, const VectorSettingsLengths &lengths, const QColor& color);
    struct VectorData {
        QVector2D value;
        QColor color;
    };
    struct VectorParam
    {
        QVector2D pixLenVector;
        QColor color;
    };
    static void drawVector(QPainter *painter, const VectorParam &vectorParam, float lineWidth);
    static void drawTriangle(QPainter *painter,
                             const VectorParam &vectorParam1, const VectorParam &vectorParam2, const VectorParam &vectorParam3,
                             float lineWidth);
private:
    static void drawVectorLine(QPainter *painter, const VectorParam &vectorParam, float lineWidth);
    static void drawArrowHead(QPainter *painter, const VectorParam &vectorParam);
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
