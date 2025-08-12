#include "vectorsettingsstatic.h"
#include "vectorpaintcalc.h"
#include <QFont>

VectorSettingsStatic::VectorType VectorSettingsStatic::getVectorType(int vectorIdx)
{
    return vectorIdx < VectorSettingsStatic::COUNT_PHASES ? TYPE_U : TYPE_I;
}

float VectorSettingsStatic::getCoordCrossAndCircleLineWidth(const QPainter *painter)
{
    return VectorPaintCalc::getClipSquareLen(painter) * 0.004;
}

float VectorSettingsStatic::getVectorLineWidth(const QPainter *painter)
{
    return VectorPaintCalc::getClipSquareLen(painter) * 0.01;
}

float VectorSettingsStatic::getArrowHeight(const QPainter *painter)
{
    return VectorPaintCalc::getClipSquareLen(painter) * 0.03;
}

float VectorSettingsStatic::getArrowSpreadAngle()
{
    return degToRad(22.5);
}

float VectorSettingsStatic::getCenterDotDiameter(const QPainter *painter)
{
    return getVectorLineWidth(painter);
}
