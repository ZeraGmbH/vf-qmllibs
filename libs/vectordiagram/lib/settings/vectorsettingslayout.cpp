#include "vectorsettingslayout.h"
#include "vectorpaintcalc.h"

bool VectorSettingsLayout::getCoordCrossVisible() const
{
    return m_coordCrossVisible;
}

void VectorSettingsLayout::setCoordCrossVisible(bool coordCrossVisible)
{
    m_coordCrossVisible = coordCrossVisible;
}

bool VectorSettingsLayout::getCircleVisible() const
{
    return m_circleVisible;
}

void VectorSettingsLayout::setCircleVisible(bool circleVisible)
{
    m_circleVisible = circleVisible;
}

float VectorSettingsLayout::getCoordCrossAndCircleLineWidthRel() const
{
    return m_coordCrossAndCircleLineWidthRel;
}

void VectorSettingsLayout::setCoordCrossAndCircleLineWidthRel(float coordCrossAndCircleLineWidthRel)
{
    m_coordCrossAndCircleLineWidthRel = coordCrossAndCircleLineWidthRel;
}

float VectorSettingsLayout::getCoordCrossAndCircleLineWidth(const QPainter *painter) const
{
    return VectorPaintCalc::getClipSquareLen(painter) * m_coordCrossAndCircleLineWidthRel;
}

QColor VectorSettingsLayout::getCoordCrossColor() const
{
    return m_coordCrossColor;
}

void VectorSettingsLayout::setCoordCrossColor(QColor coordCrossColor)
{
    m_coordCrossColor = coordCrossColor;
}

QColor VectorSettingsLayout::getCircleColor() const
{
    return m_circleColor;
}

void VectorSettingsLayout::setCircleColor(QColor circleColor)
{
    m_circleColor = circleColor;
}

float VectorSettingsLayout::getCenterDotDiameterRel() const
{
    return m_centerDotDiameterRel;
}

void VectorSettingsLayout::setCenterDotDiameterRel(float centerDotDiameterRel)
{
    m_centerDotDiameterRel = centerDotDiameterRel;
}

float VectorSettingsLayout::getCenterDotDiameter(const QPainter *painter) const
{
    return VectorPaintCalc::getClipSquareLen(painter) * m_centerDotDiameterRel;
}

float VectorSettingsLayout::getVectorLineWidthRel() const
{
    return m_vectorLineWidthRel;
}

void VectorSettingsLayout::setVectorLineWidthRel(float vectorLineWidthRel)
{
    m_vectorLineWidthRel = vectorLineWidthRel;
}

float VectorSettingsLayout::getVectorLineWidth(const QPainter *painter) const
{
    return VectorPaintCalc::getClipSquareLen(painter) * m_vectorLineWidthRel;
}

float VectorSettingsLayout::getArrowHeight(const QPainter *painter) const
{
    return VectorPaintCalc::getClipSquareLen(painter) * m_arrowHeightRel;
}

float VectorSettingsLayout::getArrowSpreadAngle() const
{
    return degToRad(m_arrowSpreadAngleRel);
}

float VectorSettingsLayout::getLabelVectorOvershootFactor() const
{
    return m_labelVectorOvershootFactor;
}

void VectorSettingsLayout::setLabelVectorOvershootFactor(float labelVectorOvershootFactor)
{
    m_labelVectorOvershootFactor = labelVectorOvershootFactor;
}

float VectorSettingsLayout::getLabelFontSize() const
{
    return m_labelFontSize;
}

void VectorSettingsLayout::setLabelFontSize(float labelFontSize)
{
    m_labelFontSize = labelFontSize;
}

QFont VectorSettingsLayout::getLabelFont(const QPainter *painter) const
{
    QFont defaultFont;
    defaultFont.setPointSizeF(VectorPaintCalc::getClipSquareLen(painter) * m_labelFontSize);
    defaultFont.setFamily("Sans");
    defaultFont.setWeight(QFont::Medium);
    return defaultFont;
}

