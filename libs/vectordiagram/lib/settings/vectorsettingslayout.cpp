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

float VectorSettingsLayout::getCoordCrossAndCircleLineWidth() const
{
    return m_coordCrossAndCircleLineWidth;
}

void VectorSettingsLayout::setCoordCrossAndCircleLineWidth(float coordCrossAndCircleLineWidth)
{
    m_coordCrossAndCircleLineWidth = coordCrossAndCircleLineWidth;
}

float VectorSettingsLayout::getCoordCrossAndCircleLineWidthPix(const QPainter *painter) const
{
    return VectorPaintCalc::getClipSquareLen(painter) * m_coordCrossAndCircleLineWidth;
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

float VectorSettingsLayout::getCenterDotDiameterPix(const QPainter *painter) const
{
    // Use m_vectorLineWidth
    return VectorPaintCalc::getClipSquareLen(painter) * std::max(m_vectorLineWidthU, m_vectorLineWidthI);
}

float VectorSettingsLayout::getVectorLineWidthU() const
{
    return m_vectorLineWidthU;
}

void VectorSettingsLayout::setVectorLineWidthU(float vectorLineWidth)
{
    m_vectorLineWidthU = vectorLineWidth;
}

float VectorSettingsLayout::getVectorLineWidthI() const
{
    return m_vectorLineWidthI;
}

void VectorSettingsLayout::setVectorLineWidthI(float vectorLineWidth)
{
    m_vectorLineWidthI = vectorLineWidth;
}

float VectorSettingsLayout::getVectorLineWidthPix(const QPainter *painter, PhaseType phaseType) const
{
    return VectorPaintCalc::getClipSquareLen(painter) *
           (phaseType==PhaseType::TYPE_U ? m_vectorLineWidthU : m_vectorLineWidthI);
}

float VectorSettingsLayout::getArrowHeight() const
{
    return m_arrowHeight;
}

void VectorSettingsLayout::setArrowHeight(float arrowHeight)
{
    m_arrowHeight = arrowHeight;
}

float VectorSettingsLayout::getArrowHeightPix(const QPainter *painter) const
{
    return VectorPaintCalc::getClipSquareLen(painter) * m_arrowHeight;
}

float VectorSettingsLayout::getArrowSpreadAngleDeg() const
{
    return m_arrowSpreadAngleDeg;
}

float VectorSettingsLayout::getArrowSpreadAngle() const
{
    return degToRad(m_arrowSpreadAngleDeg);
}

void VectorSettingsLayout::setArrowSpreadAngleDeg(float arrowSpreadAngle)
{
    m_arrowSpreadAngleDeg = arrowSpreadAngle;
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

