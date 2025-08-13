#ifndef VECTORPAINTCALC_H
#define VECTORPAINTCALC_H

#include "vectorsettings.h"
#include "vectorconstants.h"
#include <QPainter>
#include <QVector2D>
#include <math.h>

#define degToRad(degree) ((degree) * M_PI / 180.0)
#define radToDeg(radian) ((radian) * 180.0 / M_PI)

struct VectorSettingsEx {
    const VectorSettings &vectorSetttings;
    PhaseType phaseType;
};

class VectorPaintCalc
{
public:
    static int getHeight(const QPainter *painter);
    static int getWidth(const QPainter *painter);
    static float centerX(const QPainter *painter);
    static float centerY(const QPainter *painter);
    static float getClipSquareLen(const QPainter *painter);
    static QVector2D calcVectorOtherLen(const QVector2D &vector, float len);
    static QVector2D calcPixVec(QPainter *painter, const VectorSettingsEx &vectorSettingsEx,
                                const QVector2D &value,
                                float shorten = 0.0);
};

#endif // VECTORPAINTCALC_H
