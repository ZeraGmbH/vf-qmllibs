#ifndef VECTORPRIMITIVESPAINTER_H
#define VECTORPRIMITIVESPAINTER_H

#include "vectorsettingsgeometry.h"
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
    static void drawVector(QPainter *painter, const VectorSettingsGeometry &geomSetttings, float nominalValue,
                           const VectorData &vector);
    static void drawTriangle(QPainter *painter, const VectorSettingsGeometry &geomSetttings, float nominalValue,
                             const VectorData &vector1, const VectorData &vector2, const VectorData &vector3);
private:
    static void drawVectorLine(QPainter *painter, const VectorSettingsGeometry &geomSetttings, float nominalValue,
                               const VectorData &vector);
    static void drawArrowHead(QPainter *painter, const VectorSettingsGeometry &geomSetttings, float nominalValue,
                              const VectorData &vector);
    static QVector2D calcPixVec(QPainter *painter, const VectorSettingsGeometry &geomSetttings,
                                float nomValue, const QVector2D &value, float shortenPixels = 0.0);
    static QPolygonF lineToRectangleForSvgGradient(const QPoint &start, const QPoint &end, int width);
};

#endif // VECTORPRIMITIVESPAINTER_H
