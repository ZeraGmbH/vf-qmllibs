#ifndef VECTORPRIMITIVESPAINTER_H
#define VECTORPRIMITIVESPAINTER_H

#include "vectorpaintcalc.h"
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
    static void drawVector(QPainter *painter, const GeometryParam &geomParam,
                           const VectorData &vector);
    static void drawTriangle(QPainter *painter, const GeometryParam &geomParam,
                             const VectorData &vector1, const VectorData &vector2, const VectorData &vector3);
private:
    static void drawVectorLine(QPainter *painter, const GeometryParam &geomParam,
                               const VectorData &vector);
    static void drawArrowHead(QPainter *painter, const GeometryParam &geomParam,
                              const VectorData &vector);
    struct PointData {
        QPoint point;
        QColor color;
    };
    static void drawGradientLine(QPainter *painter, const float lineWidth,
                                 const PointData &pt1, const PointData &pt2);
    static QPolygonF lineToRectangleForSvgGradient(const QPoint &start, const QPoint &end,
                                                   float width, float shortenBothEnds = 0);
};

#endif // VECTORPRIMITIVESPAINTER_H
