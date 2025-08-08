#ifndef VECTORSETTINGSSTATIC_H
#define VECTORSETTINGSSTATIC_H

#include <QPainter>

class VectorSettingsStatic
{
public:
    static constexpr int COUNT_PHASES = 3;
    static constexpr int COUNT_VECTORS = COUNT_PHASES*2;
    static float getGridAndCircleLineWidth(const QPainter *painter);
    static float getVectorLenMaxInPixels(const QPainter *painter);
    static float getVectorLineWidth(const QPainter *painter);
    static float getArrowHeight(const QPainter *painter);
    static float getArrowSpreadAngle();
    static void setFontForLabels(QPainter *painter);
};

#endif // VECTORSETTINGSSTATIC_H
