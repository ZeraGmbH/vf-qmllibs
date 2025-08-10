#ifndef VECTORPRIMITIVESPAINTER_H
#define VECTORPRIMITIVESPAINTER_H

#include "vectorsettingsgeometry.h"
#include <QPainter>
#include <QColor>
#include <QVector2D>

class VectorPrimitivesPainter
{
public:
    static void drawCoordCross(QPainter *painter, const QColor& color);
    static void drawCircle(QPainter *painter, const VectorSettingsLengths &lengths, const QColor& color);
    struct VectorData {
        const QVector2D value;
        const QColor color;
    };
    static void drawVector(QPainter *painter, const VectorSettingsGeometry &geomSetttings, float nominalValue,
                           const VectorData &vector);
private:
    static void drawVectorLine(QPainter *painter, const VectorSettingsGeometry &geomSetttings, float nominalValue,
                               const VectorData &vector);
    static void drawArrowHead(QPainter *painter, const VectorSettingsGeometry &geomSetttings, float nominalValue,
                              const VectorData &vector);
    static QVector2D calcPixVec(QPainter *painter, const VectorSettingsGeometry &geomSetttings,
                                float nomValue, const QVector2D &value, float shortenPixels = 0.0);
};

#endif // VECTORPRIMITIVESPAINTER_H
