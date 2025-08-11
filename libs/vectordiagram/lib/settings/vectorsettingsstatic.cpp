#include "vectorsettingsstatic.h"
#include "vectorpaintcalc.h"
#include <QFont>

VectorSettingsStatic::VectorType VectorSettingsStatic::getVectorType(int vectorIdx)
{
    return vectorIdx < VectorSettingsStatic::COUNT_PHASES ? TYPE_U : TYPE_I;
}

float VectorSettingsStatic::getGridAndCircleLineWidth(const QPainter *painter)
{
    return VectorPaintCalc::getClipSquareLen(painter) * 0.005;
}

float VectorSettingsStatic::getVectorLenMaxInPixels(const QPainter *painter)
{
    constexpr float totalLenAvail = 1.0;
    constexpr float extraLabelLenFromAvail = 0.2;
    constexpr float vectorLenFromAvail = totalLenAvail - extraLabelLenFromAvail;

    const float pixelsAvailforVector = VectorPaintCalc::getClipSquareLen(painter) / 2 * vectorLenFromAvail;
    return pixelsAvailforVector;
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

void VectorSettingsStatic::setFontForLabels(QPainter *painter)
{
    const int minXy = std::min(VectorPaintCalc::getHeight(painter), VectorPaintCalc::getWidth(painter));
    QFont defaultFont;
    defaultFont.setPixelSize(minXy > 0.0 ? minXy / 25 : 10.0);
    defaultFont.setFamily("Sans");
    painter->setFont(defaultFont);
}
