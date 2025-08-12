#include "vectorsettingslayout.h"
#include "vectorpaintcalc.h"

float VectorSettingsLayout::getLabelVectorOvershootFactor()
{
    return m_labelVectorOvershootFactor;
}

QFont VectorSettingsLayout::getDefaultFont(const QPainter *painter)
{
    QFont defaultFont;
    defaultFont.setPointSizeF(VectorPaintCalc::getClipSquareLen(painter) * m_labelFontSize);
    defaultFont.setFamily("Sans");
    defaultFont.setWeight(QFont::Medium);
    return defaultFont;
}
