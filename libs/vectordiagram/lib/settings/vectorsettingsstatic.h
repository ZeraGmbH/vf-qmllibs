#ifndef VECTORSETTINGSSTATIC_H
#define VECTORSETTINGSSTATIC_H

#include <QPainter>

class VectorSettingsStatic
{
public:
    static constexpr int COUNT_PHASES = 3;
    static constexpr int COUNT_VECTORS = COUNT_PHASES*2;
    enum VectorType {
        TYPE_U,
        TYPE_I
    };
    static VectorType getVectorType(int vectorIdx);
    static float getCoordCrossAndCircleLineWidth(const QPainter *painter);
    static float getVectorLenMaxInPixels(const QPainter *painter);
    static float getVectorLineWidth(const QPainter *painter);
    static float getArrowHeight(const QPainter *painter);
    static float getArrowSpreadAngle();
    static float getCenterDotDiameter(const QPainter *painter);
    static float getLabelVectorOvershootFactor();
    static void setFontForLabels(QPainter *painter);
};

#endif // VECTORSETTINGSSTATIC_H
